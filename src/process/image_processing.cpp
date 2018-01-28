// Copyright Pierre-Jean LARTAUD
// 5A GBM Polytech Lyon / M2 MISS Lyon1
// 2017/2018

//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//-------------------------------- Projet 5A -------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//

// ce fichier a pour but de faire la transition entre octave et le c++, via le shell


#include "image_processing.h"
using namespace std;

//--------------------------------------------------------------------------//
//-------------------------------- numeration ------------------------------//
//--------------------------------------------------------------------------//

vector<int> numeration (string img_path)
{
    cout << "Blood cells count called on" << img_path << "\n";

    system(
            ("/home/anael/eclipse-workspace/ImageProject2/Octave\\ Files/numeration.m "
                    + img_path).c_str()); //appel du script octave via le shell

	ifstream file("counts.mat", ios::in); // ouverture du fichier créé par le script octave
	if(file) //on verifie l'ouverture du fichier
	{
		//cout << "file open" << endl;
		string line;
		int GB_line = 4; // correspond aux lignes de chaque numeration de cellules
		int GR_line = 9;
		int Thr_line = 14;
 		int Cells_line = 19;
		vector<int> counts(4); // on crée un tableau qui contiendra les valeurs de numeration
		int i = 1;

		while(getline(file,line)) // on parcours le fichier jusqu'à la fin
        {
         	if(i == GB_line) // quand on atteint la ligne de GB
				{
					stringstream S(line); // on se sert du stream pour transformer un string en int
					S >> counts[0]; // et on récupère le nombre dans le tableau
				}

				if(i == GR_line) // meme chose pour les autres
				{
					stringstream S(line);
					S >> counts[1];
				}

         	if(i == Thr_line)
				{
					stringstream S(line);
					S >> counts[2];
				}

         	if(i == Cells_line)
				{
					stringstream S(line);
					S >> counts[3];
				}
            i++;
        }
        int const destroy = remove(
                "/home/pj/Progra/Polytech/5A/projet_5A/counts.mat"); // on détruit le fichier créé par le script
		return counts; // et on retourne le tableau
	}
	else
	{
		cout << "can't open file !" << endl; // on signale si impossible d'ouvrir
        int const destroy = remove(
                "/home/pj/Progra/Polytech/5A/projet_5A/counts.mat");
		exit(EXIT_FAILURE); // on sort du programme
	}
}

//--------------------------------------------------------------------------//
//--------------------------------- gommage --------------------------------//
//--------------------------------------------------------------------------//

void gommageGR (string img_path) // cette fonction appelle juste le script octave
{
    cout << "Features highlight called on" << img_path << "\n";
    system(
            ("/home/anael/eclipse-workspace/ImageProject2/Octave\\ Files/gommage.m "
                    + img_path).c_str());
}
