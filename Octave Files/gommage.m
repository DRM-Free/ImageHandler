#!/usr/bin/octave -qf

% Copyright Pierre-Jean LARTAUD
% 5A GBM Polytech Lyon / M2 MISS Lyon1 
% 2017/2018

%--------------------------------------------------------------------------%
%--------------------------------------------------------------------------%
%-------------------------------- Projet 5A -------------------------------%
%--------------------------------------------------------------------------%
%---------------------------------- gommage -------------------------------%
%--------------------------------------------------------------------------%

clear all
close all
clc
pkg load image % charge le package image avec les fcts dont nous avons besoin
warning('off', 'Octave:GraphicsMagic-Quantum-Depth'); %supprime un commentaire dû à ma version d'octave

%------------------------------------------------------------------------%
%--------------------- validation input, calcul zoom --------------------%
%------------------------------------------------------------------------%
img_path = argv(){1}; % récupère l'argument du shell, le path de l'image

img_origin = imread(img_path); % lecture de l'image
if(numel (img_origin) == 1) % si l'image n'a qu'un pixel, ce n'est pas une image valide
  display ('invalid image argument');
  return;
end

if (max(max(img_origin(:,:,1))) > 245) % verification du zoom : les images au zoom 4000 ont une composante rouge plus faible, qui ne sature pas
  zoom = 400;  % cela permettra de lancer un algorithme adapté au zoom, et à sa colorimétrie
else
  zoom = 4000;  
end

%---------------------------------------------------------------------------%
%-------------------------------- zoom 400 ---------------------------------%
%---------------------------------------------------------------------------%

if (zoom == 400)  % lancement de l'algo pour le zoom 400
  %----------- isolation des GB + thrombo ------------%
  img_blue =  1.5*img_origin(:,:,3) - 0.1*img_origin(:,:,1) - img_origin(:,:,2); % on maximise la composante bleue, plus forte chez les Thr et GB, pour récupérer que ces derniers
  max = max(max(img_blue));
  min = min(min(img_blue));
  img_blue_max = (img_blue-min)*(255/(max-min)); % étalement pour facilité la binarisation
 
  img_blue_BW = im2bw(img_blue_max,0.2); % binarisation
  img_blue_BW = bwareaopen(img_blue_BW,5000); % on supprime les petits objets parasite de -5000 pixels, qui fausserait l'algo
  img_blue_BW = medfilt2 (img_blue_BW, [25 25]); % on fait un filtre médian pour supprimer le bruit restant et lisser l'image
  
	%------- suppression des GR sur image couleur ------%
	GB_thrombo = img_origin;
	dim_x = size (img_blue_BW,1); %recuperation dimensions
	dim_y = size (img_blue_BW,2);
	for i = 1:dim_x  % parcours de l'image par ligne et colonne
	  for j = 1:dim_y
		 if (img_blue_BW(i,j) == 0) 	% on parcours l'image binarisé des GB et Thr. Si les pixels valent 0 (noir), ce n'est pas un Thr ou GR
		  GB_thrombo(i,j,1) = 218;		% on peut alors prendre ses coordonnées, et transformé les pixels dans les valeurs RGB moyennes du fond de l'image
			GB_thrombo(i,j,2) = 193;	% cela à pour effet de "gommer" les GR
			GB_thrombo(i,j,3) = 145;
		 end
	  end
	end
	img_gom = GB_thrombo;
  img_gom_path = strcat (img_path(1:end-4),'_gomGR.PNG'); % on supprime l'extension de l'image original et on renomme pour qu'elles soient dans le répertoire
  imwrite (img_gom,img_gom_path) % on l'enregistre

%---------------------------------------------------------------------------%
%-------------------------------- zoom 4000 --------------------------------%
%---------------------------------------------------------------------------%

elseif (zoom == 4000) % même chose que précédemment, avec le zoom 4000. certains parametres changent, à cause de la variation de la colorimétrie

	%----------- isolation des GB + thrombo ------------%
	img_blue = img_origin(:,:,3) - 0.5*(img_origin(:,:,1)) - 0.5*(img_origin(:,:,2));
	max = max(max(img_blue));
	min = min(min(img_blue));
	img_blue_max = (img_blue-min)*(255/(max-min));
	img_blue_BW = im2bw(img_blue_max,0.13);
	img_blue_BW = bwareaopen(img_blue_BW,1000);

  %------- suppression des GR sur image couleur ------%
	GB_thrombo = img_origin;
	dim_x = size (img_blue_BW,1); %recuperation dimensions
	dim_y = size (img_blue_BW,2);
	for i = 1:dim_x  % parcours de l'image par ligne et colonne
	  for j = 1:dim_y
		 if (img_blue_BW(i,j) == 0) 
			GB_thrombo(i,j,1) = 146;
			GB_thrombo(i,j,2) = 146;
			GB_thrombo(i,j,3) = 146;
		 end
	  end
	end
  img_gom = GB_thrombo;
  img_gom_path = strcat (img_path(1:end-4),'_gomGR.PNG'); 
  imwrite (img_gom,img_gom_path)

end
