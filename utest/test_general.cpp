//
// Created by marina on 30/10/23.
//
#include "gtest/gtest.h"
#include "sim/calculos.hpp"
#include "sim/simulacion.cpp"
#include <fstream>

TEST(unitarias, uno){
  EXPECT_EQ(1,1);
}
TEST(unitarias, dos){
  EXPECT_EQ(3,3);
}
/*
TEST(calculos,uno){
 const vector<string> vec = {"1", "../small.fld","../out.fld"};
 simulation(vec);
 ifstream archivo1;
 ifstream archivo2;
 archivo1.open("../boundint-base-5.trz", ios::binary);
 archivo2.open( "../out.fld", ios::binary);
 ASSERT_EQ(archivo2, archivo1);
}
*/
