#!/usr/bin/octave -qf

% Copyright Pierre-Jean LARTAUD
% 5A GBM Polytech Lyon / M2 MISS Lyon1 
% 2017/2018

%--------------------------------------------------------------------------%
%--------------------------------------------------------------------------%
%-------------------------------- Projet 5A -------------------------------%
%--------------------------------------------------------------------------%
%------------------------------- numeration -------------------------------%
%--------------------------------------------------------------------------%

clear all
close all
clc
pkg load image % charge le package image
warning('off', 'Octave:GraphicsMagic-Quantum-Depth'); %supprime un commentaire dû à ma version d'octave

%------------------------------------------------------------------------%
%--------------------- validation input, calcul zoom --------------------%
%------------------------------------------------------------------------%
img_path = argv(){1}; % récupère l'argument du shell, le path de l'image

img_origin = imread(img_path); % lecture de li'image
if(numel (img_origin) == 1) % si l'image n'a qu'un pixel, ce n'est pas valide
  display ('invalid image argument');
  return;
end

if (max(max(img_origin(:,:,1))) > 245) % verification du zoom : les images au zoom 4000 ont une composante rouge plus faible, qui ne sature pas
  zoom = 400; % cela permettra de lancer un algorithme adapté au zoom, et à sa colorimétrie
else
  zoom = 4000;  
end

%------------------------------------------------------------------------%
%------------------------------- zoom 400 -------------------------------%
%------------------------------------------------------------------------% 

if((zoom) == 400) %Les Thr ne sont pas compté au zoom 400, trop petites
 
  %------------------ numeration GB ------------------%
  img_GB_blue =  1.5*img_origin(:,:,3) - 0.1*img_origin(:,:,1) - img_origin(:,:,2); % on maximise le bleu, plus présent dans les GB
  max = max(max(img_GB_blue));
  min = min(min(img_GB_blue));
  img_GB_blue_max = (img_GB_blue-min)*(255/(max-min)); % étalement pour facilité la binarisation
  
  img_GB_BW = im2bw(img_GB_blue_max,0.2); % binarisation pour récupérer (au mieux) que les GB
  img_GB_BW = bwareaopen(img_GB_BW,5000); % suppression des petits objets parasites
  img_GB_BW = medfilt2 (img_GB_BW, [25 25]); % filtrage median pour supprimer le bruit parasite, et lisser les objets
  
  [GB_index_img_array,GB_count] = bwlabel(img_GB_BW); % on utilise bwlabel pour compter les objets, en les discréminant par leur surface. 
  
  for i= 1 : GB_count % pour chaque objet, on calcule sa surface
    GB_separate(:,:,i) = GB_index_img_array == i;
  end
  GB_area = sum(sum(GB_separate));
  num_GB = 0; 
  for i = 1 : GB_count
    if (GB_area(:,:,i) > 5000) % si l'objet est inférieure à la surface minimale d'un GB, il n'est pas compté
      num_GB = num_GB + 1;
    end
  end
  num_GB;
  % les surfaces minimales, maximales et moyennes des différentes cellules ont été trouvé grâce à une étude statistique. Voir le dossier "statistical studies"  

  %------------------ numeration GR ------------------%
  img_GR_blue = img_origin(:,:,3)*1.5; % les GR sont plus rouges que les autres cellules, ont maximise cette composante pour les récupérer 
  img_GR_BW = ~(im2bw (img_GR_blue, 0.77)); % on binarise
  SE1 = strel ('line', 3, 0); 
  SE2 = strel ('line', 3, 90);
  img_GR_BW_ferm = imdilate (img_GR_BW, SE1); % on fait une dilatation verticale et horizontale pour fermer les GR, qui sinon seraient compter plusieurs fois
  img_GR_BW_ferm = imdilate (img_GR_BW_ferm, SE2);
  img_GR_BW_ferm = bwareaopen (img_GR_BW_ferm, 1000); % on supprime les petits objets parasites
  img_GR_BW_ferm = bwfill(img_GR_BW_ferm,'holes',8); % on remplit encore les GR, pour éviter le comptage à plusieurs reprises 
  img_GR_separate = bwareafilt(img_GR_BW_ferm, [1500 6000]); % il a trop de GR pour la fonction bwlabel, on doit trouver une autre manière. On sépare ici l'image en 2 : une ou les GR sont bien séparés, d'une taille comprise en 1500 et 6000 (donnée grâce à l'étude statistique), et l'autre où on aura les GR superposés
  cc = bwconncomp (img_GR_separate); % on compte les GR bien séparés
  num_GR = cc.NumObjects;
  img_GR_overlap = bwareafilt(img_GR_BW_ferm, [6001 10000000]); % on crée l'image avec seuelement les GR superposés
  [GR_index_img_array, GR_count] = bwlabel(img_GR_overlap); % on peut maintenant utliser bwlabel pour calculer leur surface
  for i = 1:GR_count % calcul de la surface de tout les objets superposé
    GR_separate(:,:,i) = GR_index_img_array == i;
  end
  GR_area = sum(sum(GR_separate));
  for i = 1:GR_count
    num_GR = num_GR + round(GR_area(:,:,i) / 3965); % les objets de cette image étant tous plus grand que le plus gros GR observé, on divise leur tailles par la taille d'un GR moyen pour obtenir une approximation du nombre de GR superposés, auquel on ajoute les GR séparés précédemment calculés 
  end
  num_GR;  
  
  %---------- comptage total et sauvegarde -----------%
  num_Cells = num_GB + num_GR; % nombre total de cellules
  num_Thr = NaN; % les Thr ne sont pas comptés
  save ('counts.mat', 'num_GB', 'num_GR', 'num_Thr', 'num_Cells'); % on enregistre les données, pour qu'elles soient récupérées par les fonctions C++

%------------------------------------------------------------------------%  
%------------------------------- zoom 4000 ------------------------------%
%------------------------------------------------------------------------%
  
elseif(zoom == 4000) % même chose que précédemment pour 4000. Les méthodes utilisés sont les mêmes que précédemment
  
  %------------------ numeration Thr -----------------%
  img_THR = img_origin(:,:,3) - 0.5*(img_origin(:,:,1)) - 0.5*(img_origin(:,:,2));
  max = max(max(img_THR));
  min = min(min(img_THR));
  img_THR_max = (img_THR-min)*(255/(max-min));
  img_THR_BW = im2bw(img_THR_max,0.18);
  img_THR_BW = bwareaopen(img_THR_BW,1200);
  SE = strel ('disk', 12, 0);
  img_THR_BW_ouv = imopen (img_THR_BW, SE);
  [Thr_index_img_array, Thr_count] = bwlabel(img_THR_BW_ouv);
  Thr_count;
  
  for i= 1 : Thr_count
    Thr_separate(:,:,i) = Thr_index_img_array == i; 
  end
  
  Thr_area = sum(sum(Thr_separate));
  num_Thr = 0; 
  for i = 1 : Thr_count
    if ((Thr_area(:,:,i) > 1000) && ((Thr_area(:,:,i) < 7000))) % l'image présente ici GB + Thr. On discrimine donc en surface pour éliminer à la fois les GB et le bruit
      num_Thr = num_Thr + 1;
    end
  end
  num_Thr;
  
  %------------------ numeration GB ------------------%
  img_GB_BW = bwareaopen(img_THR_BW_ouv,8500); % on récupère l'image précédente avec Thr + GB, et on filtre les petits objets pour supprimer les Thr
  
  [GB_index_img_array, GB_count] = bwlabel(img_GB_BW);
  GB_count;
  if (GB_count > 0)
    for i= 1 : GB_count
      GB_separate(:,:,i) = GB_index_img_array == i; 
    end
    
    GB_area = sum(sum(GB_separate));
    
    num_GB = 0; 
    for i = 1 : GB_count
      if (GB_area(:,:,i) > 28000) % on fixe une taille minimale de GB
        num_GB = num_GB + 1;
      end
    end
    num_GB;
  else num_GB = 0;
  end
  
  %------------------ numeration GR ------------------%
  img_ntsc = rgb2ntsc(img_origin); 
  img_ntsc = im2uint8(img_ntsc);
  img_ntsc_sat = img_ntsc(:,:,3); % on récupère la saturation de l'image, où les GR sont le plus visibles.
  level = graythresh(img_ntsc_sat);
  img_GR_BW = im2bw(img_ntsc_sat,level); 
  img_GR_BW_med = medfilt2 (img_GR_BW, [15 15]);
  img_GR_BW_med = bwfill (img_GR_BW_med, 'holes', 8); % on remplit les GR
  SE = ones (30);
  img_GR_BW_med = img_GR_BW_med - img_THR_BW_ouv; % on enleve de l'image les GB et Thr en soustrayant l'image (Thr + GB)
  img_GR_BW_med_ouv = imopen (img_GR_BW_med, SE);
  num_GR = 0;
  [GR_index_img_array, GR_count] = bwlabel(img_GR_BW_med); % pas besoin de séparer l'image en 2 comme en x400 ici, il y a a suffisamment peu d'objets
  GR_count;
  
  for i= 1 : GR_count
    GR_separate(:,:,i) = GR_index_img_array == i; 
  end
  
  GR_area = sum(sum(GR_separate));
  
  for i = 1 : GR_count
    if ((GR_area(:,:,i) < 31000) && (GR_area(:,:,i) > 7000))  % on discrimine par surface
      num_GR = num_GR + 1;
    elseif (GR_area(:,:,i) > 31000)
      num_GR = num_GR + round (GR_area(:,:,i)/20131); % si l'objet est trop gros, on divise sa surface par la surface moyen d'un GR pour avoir le nombre de GR en overlapping
    end
  end
  num_GR;
  
  %---------- comptage total et sauvegarde -----------%
  num_Cells = num_GB + num_GR + num_Thr; % toutes les cellules comptés 
  save ('counts.mat', 'num_GB', 'num_GR', 'num_Thr', 'num_Cells'); % on enregistre pour pouvoir récupérer l'info via C++
end  

