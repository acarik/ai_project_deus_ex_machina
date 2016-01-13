//---------------------------------------------------------------------------


#pragma hdrstop
#include "Game_State.h"
   #include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

Game_State::Game_State(int _Data[Board_Size][Board_Size], Game_State* _back_pointer, int _Cost, int _Number_of_Possible_Moves){

for (int i = 0; i <= Board_Size-1; i++) {
	for (int j = 0; j <= Board_Size-1; j++) {
          Data[i][j] = _Data[i][j];
	}
}
Back_Pointer = _back_pointer;
Cost = _Cost;

Number_of_Possible_Moves = Calculate_Possible_Moves(&Data);

}
bool Check_Cell(int (*State_Data)[Board_Size][Board_Size],int i,int j, int oppn_color)
{
if (i < 0)
	return false;
if (i >= Board_Size)
	return false;
if (j < 0)
	return false;
if (j >= Board_Size)
	return false;
if ((*State_Data)[i][j] == oppn_color)
	return true;
return false;
}

bool Is_Potential_Cell(int (*State_Data)[Board_Size][Board_Size], int x, int y)
{
// isolated_cell: kendisi bos olan ve en az bir komsusu dolu olan hucre.
if ((*State_Data)[x][y] != empty)
	return false;
for (int i = x-1; i <= x+1; i++) {
	if (i < 0)
		continue;
	if (i >= Board_Size)
		continue;
	for (int j = y-1; j <= y+1; j++) {
		if (j < 0)
			continue;
		if (j >= Board_Size)
			continue;
		if (i == 0 && j == 0)
			continue;
		if ((*State_Data)[i][j] != empty)
			return true;
	}
}
return false;
/*
if ( ( ((i-1)<=7) && ((i-1)>=0) && ((j-1)<=7) && ((j-1)>=0) &&
((*State_Data)[i-1][j-1]!= empty)) ||
( ((i)>=0) && ((i)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i][j-1]!= empty)) ||
( ((i+1)>=0) && ((i+1)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i+1][j-1]!= empty)) ||
( ((i-1)>=0) && ((i-1)<=7) && ((j)>=0) && ((j)<=7) && ((*State_Data)[i-1][j]!= empty)) ||
( ((i+1)>=0) && ((i+1)<=7) && ((j)>=0) && ((j)>=0) && ((*State_Data)[i+1][j]!= empty)) ||
( ((i-1)>=0) && ((i-1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i-1][j+1]!= empty)) ||
( ((i)>=0) && ((i)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i][j+1]!= empty)) ||
( ((i+1)>=0) && ((i+1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i+1][j+1]!= empty)) ) {
 */
}

int Calculate_Possible_Moves(int (*State_Data)[Board_Size][Board_Size]){
  int number_of_possible_moves = 0;
  bool intermediate_tile = false;
  int temp[Board_Size][Board_Size];
  int curr_color = -1;
  int oppn_color = -1;
  int k = -1;
  int l = -1;
  bool flag = false;
  bool flag1 = false;
  int ci = -1;
  int cj = -1;

  for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  temp[i][j] = 	(*State_Data)[i][j];
		}
  }

  if (is_computers_turn == true)
  {
	  curr_color = white;
	  oppn_color = black;
  }
  else
  {
	  curr_color = black;
	  oppn_color = white;
  }

  for (int i = 0; i < Board_Size; i++) {
	  for (int j = 0; j < Board_Size; j++) {
		flag = Is_Potential_Cell(State_Data,i,j);
		if (flag) {
        	flag = flag;
			// sirayla her yonu kontrol et.
			for (int di = -1; di <= 1; di++) {
				for (int dj = -1; dj <= 1; dj++) {
					if (di == 0 && dj == 0)
						continue; // cunku bu bir yon degil.
					// bakalim bu hucrede rakibin tasi var miymis.
//					flag1 = Check_Cell(*State_Data,i+di,j+dj,oppn_color);
//					if (flag1) {
						// simdi bu dogrultuda ilerleyebiliriz.
						ci = i + di;
						cj = j + dj; 
						while (true){
							flag1 = Check_Cell(State_Data,ci,cj,oppn_color);
							if (!flag1)
								break;
							ci = ci + di;
							cj = cj + dj;
						}
						// eger ilerlemissek,
						// simdi geldigimiz hucre kendi rengimizse [i,j] noktasi bir possible move'dur.
						if ((ci == i + di) && (cj == j + dj)) {
							// demek ki hic ilerlememisiz.
						}
						else{
                        	flag1 = Check_Cell(State_Data,ci,cj,curr_color);
							if (flag1)
								temp[i][j] = possible_move;
						}
//					}
				}
			}
		}
	  }
  }

//
//  for (int i = 0; i <= Board_Size-1; i++) {
//	for (int j = 0; j <= Board_Size-1; j++) {
//		  if ( (*State_Data)[i][j] == empty ) {
//			 if ( ( ((i-1)<=7) && ((i-1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i-1][j-1]!= empty)) || ( ((i)>=0) && ((i)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i][j-1]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i+1][j-1]!= empty)) || ( ((i-1)>=0) && ((i-1)<=7) && ((j)>=0) && ((j)<=7) && ((*State_Data)[i-1][j]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j)>=0) && ((j)>=0) && ((*State_Data)[i+1][j]!= empty)) || ( ((i-1)>=0) && ((i-1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i-1][j+1]!= empty)) || ( ((i)>=0) && ((i)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i][j+1]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i+1][j+1]!= empty)) ) {
//				 /* Etrafý tamamen boþ olmayan fakat kendisi boþ olan bir hücre bulduk.
//					Bu hücre potansiyel bir legal hamle.*/
////				 if (is_computers_turn == false) { // Oyuncunun hamle sýrasý (konacak olan taþ siyah)
//
//					if (( ((i-1)<=7) && ((i-1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i-1][j-1]!= empty)) && ((*State_Data)[i-1][j-1]!= oppn_color)) {
//					   /*Sol üst çapraz dolu ise bu yönde ara*/
//					   l = j-1;
//					   for (k = i-1; k >= 0; k--) {
//							if (l >= 0)
//								if ((*State_Data)[k][l] == oppn_color)
//									intermediate_tile = true;
//							k--;
//							l--;
//							}
//
//					}
//					if (( ((i)<=7) && ((i)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i][j-1]!= empty)) && ((*State_Data)[i][j-1]!= oppn_color))  {
//					   /*Yukarýsý dolu ise bu yönde ara*/
//						  for (l = j-1; l >= 0; l--) {
//							 if ((*State_Data)[i][l] == oppn_color) {
//								intermediate_tile = true;
//							 }
//						  }
//					}
//					if (( ((i+1)<=7) && ((i+1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i+1][j-1]!= empty)) && ((*State_Data)[i+1][j-1]!= oppn_color))  {
//					   /*Sað üst çapraz dolu ise bu yönde ara*/
//					   l = j-1;
//					   for (k = i+1; k <= Board_Size-1; k++) {
//						if(l >= 0)
//							 if ((*State_Data)[k][l] == oppn_color)
//								intermediate_tile = true;
//						l--;
//						k++;
//						  }
//					}
//					if (( ((i+1)<=7) && ((i+1)>=0) && ((j)<=7) && ((j)>=0) && ((*State_Data)[i+1][j]!= empty)) && ((*State_Data)[i+1][j]!= oppn_color))  {
//					   /*Sað dolu ise bu yönde ara*/
//					   for (k = i+1; k <= Board_Size-1; k++) {
//							 if ((*State_Data)[k][j] == oppn_color) {
//								intermediate_tile = true;
//							 }
//					   }
//					}
//					if (( ((i+1)<=7) && ((i+1)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i+1][j+1]!= empty)) && ((*State_Data)[i+1][j+1]!= oppn_color))  {
//					   /*Sað alt çapraz dolu ise bu yönde ara*/
//					   l = j+1;
//					   for (k = i+1; k <= Board_Size-1; k++) {
//							if(l <= Board_Size-1)
//							 if ((*State_Data)[k][l] == oppn_color)
//								intermediate_tile = true;
//						  k++;
//						  l++;
//					   }
//					}
//					if (( ((i)<=7) && ((i)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i][j+1]!= empty)) && ((*State_Data)[i][j+1]!= oppn_color))  {
//					   /*Alt dolu ise bu yönde ara*/
//						  for (l = j+1; l <= Board_Size-1; l++) {
//							 if ((*State_Data)[i][l] == oppn_color) {
//								intermediate_tile = true;
//							 }
//						  }
//					}
//					if (( ((i-1)<=7) && ((i-1)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i-1][j+1]!= empty)) && ((*State_Data)[i-1][j+1]!= oppn_color))  {
//					   /*Sol alt çapraz dolu ise bu yönde ara*/
//					   l = j+1;
//						  for (k = i-1; k >= 0; k--) {
//							if(l <= Board_Size-1)
//							   if ((*State_Data)[k][l] == oppn_color)
//								intermediate_tile = true;
//							 k--;
//							 l++;
//					      }
//					}
//                    if (( ((i-1)<=7) && ((i-1)>=0) && ((j)<=7) && ((j)>=0) && ((*State_Data)[i-1][j]!= empty)) && ((*State_Data)[i-1][j]!= oppn_color))  {
//					   /*Sol dolu ise bu yönde ara*/
//						  for (k = i-1; k >= 0; k--) {
//							   if ((*State_Data)[k][j] == oppn_color) {
//								intermediate_tile = true;
//							   }
//					      }
//					}
//					if (intermediate_tile){
//						number_of_possible_moves++;
//						intermediate_tile = false;
//						temp[i][j] = possible_move;
//					}
//
////			 }
//
//
//
//			 }
//		  }
//	}
//  }
//
  for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  (*State_Data)[i][j] = temp[i][j];							   
		}
  }



  Form1->Memo_Designer_Interface->Clear();
  Form1->Memo_Designer_Interface->Lines->Add("Calculated number of moves = "+IntToStr(number_of_possible_moves));



return number_of_possible_moves;
}
