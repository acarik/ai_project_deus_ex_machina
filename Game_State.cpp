//---------------------------------------------------------------------------


#pragma hdrstop
#include "Game_State.h"

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
int Calculate_Possible_Moves(int (*State_Data)[Board_Size][Board_Size]){
  int number_of_possible_moves = 0;
  bool intermediate_tile = false;
  int temp[Board_Size][Board_Size];
  
  for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  temp[i][j] = 	(*State_Data)[i][j];							   
		}
  }

  
  for (int i = 0; i <= Board_Size-1; i++) {
	for (int j = 0; j <= Board_Size-1; j++) {
		  if ( (*State_Data)[i][j] == empty ) {
			 if ( ( ((i-1)<=7) && ((i-1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i-1][j-1]!= empty)) || ( ((i)>=0) && ((i)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i][j-1]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j-1)>=0) && ((j-1)<=7) && ((*State_Data)[i+1][j-1]!= empty)) || ( ((i-1)>=0) && ((i-1)<=7) && ((j)>=0) && ((j)<=7) && ((*State_Data)[i-1][j]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j)>=0) && ((j)>=0) && ((*State_Data)[i+1][j]!= empty)) || ( ((i-1)>=0) && ((i-1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i-1][j+1]!= empty)) || ( ((i)>=0) && ((i)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i][j+1]!= empty)) || ( ((i+1)>=0) && ((i+1)<=7) && ((j+1)>=0) && ((j+1)<=7) && ((*State_Data)[i+1][j+1]!= empty)) ) {
				 /* Etrafý tamamen boþ olmayan fakat kendisi boþ olan bir hücre bulduk.
					Bu hücre potansiyel bir legal hamle.*/
				 if (is_computers_turn == false) { // Oyuncunun hamle sýrasý (konacak olan taþ siyah)

					if (( ((i-1)<=7) && ((i-1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i-1][j-1]!= empty)) && ((*State_Data)[i-1][j-1]!= black)) {
					   /*Sol üst çapraz dolu ise bu yönde ara*/
					   for (int k = i-1; k >= 0; k--) {
						  for (int l = j-1; l >= 0; l--) {
							 if ((*State_Data)[k][l] == black) {
								intermediate_tile = true;
							 }
						  k--;	 
						  }
					   } 
					}
					if (( ((i)<=7) && ((i)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i][j-1]!= empty)) && ((*State_Data)[i][j-1]!= black))  {
					   /*Yukarýsý dolu ise bu yönde ara*/
						  for (int l = j-1; l >= 0; l--) {
							 if ((*State_Data)[i][l] == black) {
								intermediate_tile = true; 
							 }
						  }
					}
					if (( ((i+1)<=7) && ((i+1)>=0) && ((j-1)<=7) && ((j-1)>=0) && ((*State_Data)[i+1][j-1]!= empty)) && ((*State_Data)[i+1][j-1]!= black))  {
					   /*Sað üst çapraz dolu ise bu yönde ara*/
					   for (int k = i+1; k <= Board_Size-1; k++) {
						  for (int l = j-1; l >= 0; l--) {
							 if ((*State_Data)[k][l] == black) {
								intermediate_tile = true; 
							 }
						  k++;
						  }						  
					   } 
					}
					if (( ((i+1)<=7) && ((i+1)>=0) && ((j)<=7) && ((j)>=0) && ((*State_Data)[i+1][j]!= empty)) && ((*State_Data)[i+1][j]!= black))  {
					   /*Sað dolu ise bu yönde ara*/
					   for (int k = i+1; k <= Board_Size-1; k++) {
							 if ((*State_Data)[k][j] == black) {
								intermediate_tile = true; 
							 }
					   } 
					}
					if (( ((i+1)<=7) && ((i+1)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i+1][j+1]!= empty)) && ((*State_Data)[i+1][j+1]!= black))  {
					   /*Sað alt çapraz dolu ise bu yönde ara*/
					   for (int k = i+1; k <= Board_Size-1; k++) {
						  for (int l = j+1; l <= Board_Size-1; l++) {
							 if ((*State_Data)[k][l] == black) {
								intermediate_tile = true; 
							 }
                          k++;
						  }
					   }  
					}
					if (( ((i)<=7) && ((i)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i][j+1]!= empty)) && ((*State_Data)[i][j+1]!= black))  {
					   /*Alt dolu ise bu yönde ara*/
						  for (int l = j+1; l <= Board_Size-1; l++) {
							 if ((*State_Data)[i][l] == black) {
								intermediate_tile = true; 
							 }
						  }
					}
					if (( ((i-1)<=7) && ((i-1)>=0) && ((j+1)<=7) && ((j+1)>=0) && ((*State_Data)[i-1][j+1]!= empty)) && ((*State_Data)[i-1][j+1]!= black))  {
					   /*Sol alt çapraz dolu ise bu yönde ara*/
						  for (int k = i-1; k >= 0; k--) {
							 for (int l = j+1; l <= Board_Size-1; l++) {
							   if ((*State_Data)[k][l] == black) {
								intermediate_tile = true; 
							   }
                             k--;
							 }
					      } 
					}
                    if (( ((i-1)<=7) && ((i-1)>=0) && ((j)<=7) && ((j)>=0) && ((*State_Data)[i-1][j]!= empty)) && ((*State_Data)[i-1][j]!= black))  {
					   /*Sol dolu ise bu yönde ara*/
						  for (int k = i-1; k >= 0; k--) {
							   if ((*State_Data)[k][j] == black) {
								intermediate_tile = true; 
							   }
					      } 
					}
					if (intermediate_tile){number_of_possible_moves++; intermediate_tile = false; temp[i][j] = possible_move;}
						
			 }



			 }
		  }
	}
  }

  for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  (*State_Data)[i][j] = temp[i][j];							   
		}
  }



  Form1->Memo_Designer_Interface->Clear();
  Form1->Memo_Designer_Interface->Lines->Add("Calculated number of moves = "+IntToStr(number_of_possible_moves));



return number_of_possible_moves;
}
