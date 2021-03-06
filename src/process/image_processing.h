// Copyright Pierre-Jean LARTAUD
// 5A GBM Polytech Lyon / M2 MISS Lyon1
// 2017/2018

//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//-------------------------------- Projet 5A -------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

vector<int> numeration (string img_path);
void gommageGR(fs::path img_path, fs::path outputPath);

#endif
