//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Reversi.h"
 /*Globals*/
Game_State* Initial_State = NULL;
Game_State* Current_State = NULL;
TImage *p_Tile_Images[Board_Size][Board_Size];
bool is_computers_turn = false; 

/*Globals ends*/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"





TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
Initialize_GUI();
}

void Initialize_GUI(){

	/*Create Game Board*/
    Form1->Caption = "Reversi V0.0" ;
	Form1->Game_Board->ColCount = Board_Size;
	Form1->Game_Board->RowCount = Board_Size;
	Form1->Game_Board->FixedCols = 0;
	Form1->Game_Board->FixedRows = 0;
	Form1->Game_Board->GridLineWidth = 4;
	Form1->Game_Board->Color = TColor(RGB(0, 120, 0));
	Form1->Game_Board->Width = Board_Size*Cell_Height_Width + (Board_Size +1)*Form1->Game_Board->GridLineWidth;
	Form1->Game_Board->Height = Board_Size*Cell_Height_Width + (Board_Size +1)*Form1->Game_Board->GridLineWidth;

	for (int i = 0; i <= Board_Size-1; i++) {
	   Form1->Game_Board->RowHeights[i] = Cell_Height_Width;
	   Form1->Game_Board->ColWidths[i] = Cell_Height_Width;
	}
	/*Create Game Board ends*/

	/*Create TImage Objects*/
	for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {

			p_Tile_Images[i][j] = new TImage (Form1);
			p_Tile_Images[i][j]->Parent = Form1->Game_Board;
			p_Tile_Images[i][j]->Width = Cell_Height_Width;
			p_Tile_Images[i][j]->Height = Cell_Height_Width;
			p_Tile_Images[i][j]->Left = Form1->Game_Board->CellRect(i,j).Left;// + Cell_Height_Width/4;
			p_Tile_Images[i][j]->Top = Form1->Game_Board->CellRect(i,j).Top;// + Cell_Height_Width/4;
			//p_Tile_Images[i][j]->Picture->LoadFromFile("white_tile.bmp");
			p_Tile_Images[i][j]->Enabled = false;
			p_Tile_Images[i][j]->Visible = false;  
		
		}
	}
	/*End of Create TImage Objects*/
    Create_Initial_State();
    Visualize_Current_State();


}

void Create_Initial_State(){
     int temp_data[Board_Size][Board_Size];
	 for (int j = 0; j <= Board_Size-1; j++) {
		 for (int i = 0; i <= Board_Size-1; i++) {
			  temp_data[i][j] = empty;
		 }
	 }
	 temp_data[3][3] = white;
	 temp_data[4][4] = white;
	 temp_data[4][3] = black;
	 temp_data[3][4] = black;
	 Initial_State = new Game_State(temp_data, NULL,0,NULL);
	 Current_State = Initial_State;
}

void Visualize_Current_State(){

	for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
			if (Current_State->Data[i][j] == white) {
				p_Tile_Images[i][j]->Picture->LoadFromFile("white_tile.bmp");
				p_Tile_Images[i][j]->Enabled = true;
				p_Tile_Images[i][j]->Visible = true;
				continue;
			}
			else if (Current_State->Data[i][j] == black) {
				p_Tile_Images[i][j]->Picture->LoadFromFile("black_tile.bmp");
				p_Tile_Images[i][j]->Enabled = true;
				p_Tile_Images[i][j]->Visible = true;
				continue;     
			}
			else if (Current_State->Data[i][j] == possible_move) {
				p_Tile_Images[i][j]->Picture->LoadFromFile("possible_move.bmp");
				p_Tile_Images[i][j]->Enabled = false;
				p_Tile_Images[i][j]->Visible = true;
				continue;
			}
			else if (Current_State->Data[i][j] == empty) {
				p_Tile_Images[i][j]->Picture->LoadFromFile("possible_move.bmp");
				p_Tile_Images[i][j]->Enabled = false;
				p_Tile_Images[i][j]->Visible = false;
				continue;
			}
		}
	}





}
//---------------------------------------------------------------------------

void __fastcall TForm1::Game_BoardClick(TObject *Sender)
{   int Col_to_Change = 0, Row_to_Change = 0;
	int X = 0, Y = 0;
	int Number_of_Possible_Moves_in_Current = 0;
	POINT p;
 	//Form1->Memo_Designer_Interface->Lines->Add("Oldu da olduu!!!");

	if (is_computers_turn == false) {
    	GetCursorPos(&p);
		X = p.x; Y = p.y;
		X = X - Form1->Left - Form1->Game_Board->Left - Form1->Game_Board->GridLineWidth;
		Y = Y - Form1->Top - Form1->Game_Board->Top - Form1->Game_Board->GridLineWidth;

		Game_Board->MouseToCell(X,Y, Col_to_Change, Row_to_Change);
		if (Current_State->Data[Col_to_Change][Row_to_Change] != possible_move) {
            return;
		}
        Current_State->Data[Col_to_Change][Row_to_Change] = black;
		for (int i = 0; i <= Board_Size-1; i++) {
			for (int j = 0; j <= Board_Size-1; j++) {
				if (Current_State->Data[i][j] == possible_move )
					 Current_State->Data[i][j] = empty;
			}           
		}
		Calculate_Resulting_State(&Current_State->Data, Col_to_Change, Row_to_Change);
		Number_of_Possible_Moves_in_Current = Calculate_Possible_Moves(&Current_State->Data);

    Visualize_Current_State();
	}

	


	/*Form1->Memo_Designer_Interface->Lines->Add("p.x = "+IntToStr(p.x)+" p.y = " + IntToStr(p.y));
	Form1->Memo_Designer_Interface->Lines->Add("Form_Left = "+IntToStr(Form1->Left)+" Form_Top = " + IntToStr(Form1->Top));
	Form1->Memo_Designer_Interface->Lines->Add("X = "+IntToStr(X)+" Y = " + IntToStr(Y));
	Form1->Memo_Designer_Interface->Lines->Add("Col = "+IntToStr(Col_to_Change)+" Row = " + IntToStr(Row_to_Change));
    */
}
//---------------------------------------------------------------------------
void Calculate_Resulting_State(int (*State_Data)[Board_Size][Board_Size], int Col_Put, int Row_Put){
  bool intermediate_tile = false;
  int temp[Board_Size][Board_Size];
  int temp_tile_color = empty, temp_col = 0, temp_row = 0;
  
  for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  temp[i][j] = 	(*State_Data)[i][j];							   
		}
   }

   temp_tile_color = (*State_Data)[Col_Put][Row_Put];


   // Ta� konan yerden sol yukar� �apraza bak
	if ( ((*State_Data)[Col_Put-1][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put-1] != empty)  ) {
		for (int i = Col_Put-1; i >= 0; i--) {
			for (int j = Row_Put-1; j >= 0; j--) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = 0;
				   break; 
				}
			}
   		}
		for (int i = Col_Put-1; i >= temp_col; i--) {
			for (int j = Row_Put-1; j >= temp_row; j--) {
			   temp[i][j] = temp_tile_color;
			}
		}		 
	}
   // Ta� konan yerden  yukar�ya bak
	if ( ((*State_Data)[Col_Put][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put][Row_Put-1] != empty)  ) {
			for (int j = Row_Put-1; j >= 0; j--) {
				if ((*State_Data)[Col_Put][j] == temp_tile_color ) {
				   temp_col = Col_Put;
				   temp_row = j;
				   break; 
				}
			}
			for (int j = Row_Put-1; j >= temp_row; j--) {
			   temp[Col_Put][j] = temp_tile_color;
			}
	}
    // Ta� konan yerden sa� yukar� �apraza bak
	if ( ((*State_Data)[Col_Put+1][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put-1] != empty)  ) {
		for (int i = Col_Put+1; i <= Board_Size-1; i++) {
			for (int j = Row_Put-1; j >= 0; j--) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = Board_Size-1;
				   break; 
				}
			}
   		}
		for (int i = Col_Put+1; i <= temp_col; i++) {
			for (int j = Row_Put-1; j >= temp_row; j--) {
			   temp[i][j] = temp_tile_color;
			}
		}		 
	}
        // Ta� konan yerden sa�a bak
	if ( ((*State_Data)[Col_Put+1][Row_Put] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put] != empty)  ) {
		for (int i = Col_Put+1; i <= Board_Size-1; i++) {
				if ((*State_Data)[i][Row_Put] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = Row_Put;
				   break; 
				}
		}
		for (int i = Col_Put+1; i <= temp_col; i++) {
			   temp[i][Row_Put] = temp_tile_color;
		}		 
	}
    // Ta� konan yerden sa� alt �apraza bak
	if ( ((*State_Data)[Col_Put+1][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put+1] != empty)  ) {
		for (int i = Col_Put+1; i <= Board_Size-1; i++) {
			for (int j = Row_Put+1; j <= Board_Size-1; j++) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = Board_Size-1;
				   break; 
				}
			}
   		}
		for (int i = Col_Put+1; i <= temp_col; i++) {
			for (int j = Row_Put+1; j <= temp_row; j++) {
			   temp[i][j] = temp_tile_color;
			}
		}		 
	}
    // Ta� konan yerden  a�a��ya bak
	if ( ((*State_Data)[Col_Put][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put][Row_Put+1] != empty)  ) {
			for (int j = Row_Put+1; j <= Board_Size-1; j++) {
				if ((*State_Data)[Col_Put][j] == temp_tile_color ) {
				   temp_col = Col_Put;
				   temp_row = j;
				   break; 
				}
			}
			for (int j = Row_Put+1; j <= temp_row-1; j++) {
               temp[Col_Put][j] = temp_tile_color;
			}
	}
    // Ta� konan yerden sol a�a�� �apraza bak
	if ( ((*State_Data)[Col_Put-1][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put+1] != empty)  ) {
		for (int i = Col_Put-1; i >= 0; i--) {
			for (int j = Row_Put+1; j <= Board_Size; j++) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = 0;
				   break; 
				}
			}
		}
		for (int i = Col_Put-1; i >= temp_col; i--) {
			for (int j = Row_Put+1; j <= temp_row; j++) {
			   temp[i][j] = temp_tile_color;
			}
		}		 
	}

	     // Ta� konan yerden sola bak
	if ( ((*State_Data)[Col_Put-1][Row_Put] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put] != empty)  ) {
		for (int i = Col_Put-1; i >= 0; i--) {
				if ((*State_Data)[i][Row_Put] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = Row_Put;
				   break; 
				}
		}
		for (int i = Col_Put-1; i >= temp_col; i--) {
			   temp[i][Row_Put] = temp_tile_color;
		}		 
	}

	for (int i = 0; i <= Board_Size-1; i++) {
		for (int j = 0; j <= Board_Size-1; j++) {
		  (*State_Data)[i][j] = temp[i][j];							   
		}
  	}

	
}
