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

int squareWeight[Board_Size][Board_Size]=	{{100,-25,10,5,5,10,-25,100},
											 {25,25,2,2,2,2,25,25},
											 {10,2,5,1,1,5,2,10},
											 {5,2,1,2,2,1,2,5},
											 {5,2,1,2,2,1,2,5},
											 {10,2,5,1,1,5,2,10},
											 {25,25,2,2,2,2,25,25},
											 {100,-25,10,5,5,10,-25,100},};

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
    randomize();
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

	if (is_computers_turn == false)
	{
		GetCursorPos(&p);
		X = p.x; Y = p.y;
		X = X - Form1->Left - Form1->Game_Board->Left - Form1->Game_Board->GridLineWidth;
		Y = Y - Form1->Top - Form1->Game_Board->Top - Form1->Game_Board->GridLineWidth;

		Game_Board->MouseToCell(X,Y, Col_to_Change, Row_to_Change);
		if (Current_State->Data[Col_to_Change][Row_to_Change] != possible_move) {
			// gecersiz bir yere tiklanmissa cik.
			return;
		}
		Current_State->Data[Col_to_Change][Row_to_Change] = black;
		// current_state'ten possible move'lari temizle.
		Clear_Possible_Moves();
		// hamle sonucunu hesapla.
		Calculate_Resulting_State(&Current_State->Data, Col_to_Change, Row_to_Change);
		is_computers_turn = true;
		Number_of_Possible_Moves_in_Current = Calculate_Possible_Moves(&Current_State->Data);
		Visualize_Current_State();
		// simdi sira bilgisayarda
		Form1->Memo_Designer_Interface->Lines->Add("Sira bilgisayarda");
	}
	else{
	// bilgisayar hamle yapiyor.
			Number_of_Possible_Moves_in_Current = Calculate_Possible_Moves(&Current_State->Data);
		while (true)
			{
			Col_to_Change = random(Board_Size-1);
			Row_to_Change = random(Board_Size-1);
			if (Current_State->Data[Col_to_Change][Row_to_Change] == possible_move) {
				// eger sans eseri olasi hamlelerden birine denk gelmisse diger
				// possible_move degerlerini temizle.
				Clear_Possible_Moves();
				// tasi koy.
				Current_State->Data[Col_to_Change][Row_to_Change] = white;
				Calculate_Resulting_State(&Current_State->Data, Col_to_Change, Row_to_Change);
				// ... ve while loop'tan cik.
				break;
				}
			}
		Form1->Memo_Designer_Interface->Lines->Add("Bilgisayar oynadi.");
		// bilgisayar oynadi.    
		is_computers_turn = false;
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
void Clear_Possible_Moves(void){
/*	for (int i = 0; i <= Board_Size-1; i++)
		for (int j = 0; j <= Board_Size-1; j++)
			if (*(State_Data)[i][j]==possible_move)
				*(State_Data)[i][j] = empty;
*/				
		for (int i = 0; i <= Board_Size-1; i++) {
			for (int j = 0; j <= Board_Size-1; j++) {
				if (Current_State->Data[i][j] == possible_move )
					 Current_State->Data[i][j] = empty;
			}
		}
}
void Calculate_Resulting_State(int (*State_Data)[Board_Size][Board_Size], int x, int y){
	bool intermediate_tile = false;
	int temp[Board_Size][Board_Size];
	int curr_color = -1;
	int ci = -1;
	int cj = -1;
	bool flag = false;
	int count = 0;
	int oppn_color = -1;
	int c = -1;

	for (int i = 0; i <= Board_Size-1; i++)
		for (int j = 0; j <= Board_Size-1; j++)
			temp[i][j] = (*State_Data)[i][j];

	curr_color = (*State_Data)[x][y];
	if (curr_color == black)
		oppn_color = white;
	else
		oppn_color = black;

	// tas konan yerin komsuluklarini ara
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (di == 0 && dj == 0)
				// bu bir yon degil.
				continue;
			ci = x + di;
			cj = y + dj;
			// dogrultu boyunca takip edelim.
			count = 0;
			while (true){
				flag = Check_Cell(State_Data,ci,cj,oppn_color);
				if (flag){
					ci = ci + di;
					cj = cj + dj;
					count++;
                }
				else
                	break;
			}
			// durdugumuz noktada bizim tas varsa super.
			flag = Check_Cell(State_Data,ci,cj,curr_color);
			if (flag) {
				// aradaki taslari kendi rengimize cevirelim.
				for (c = 0; c < count; c++) {
					ci = ci - di;
					cj = cj - dj;
					temp[ci][cj] = curr_color;
                }

			}
		}
    }


	   /*
   // Taþ konan yerden sol yukarý çapraza bak
	if ( ((*State_Data)[Col_Put-1][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put-1] != empty)  ) {
		j = Row_Put - 1;
		for (i = Col_Put-1; i >= 0; i--) {
			if(j >= 0) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = 0;
				   break;
				}
			}
			j--;
		}
		j = Row_Put-1;
		for (i = Col_Put-1; i >= temp_col; i--) {
		if (j >= temp_row)
			temp[i][j] = temp_tile_color;
		j--;
		}		 
	}
   // Taþ konan yerden  yukarýya bak
	if ( ((*State_Data)[Col_Put][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put][Row_Put-1] != empty)  ) {
			for (j = Row_Put-1; j >= 0; j--) {
				if ((*State_Data)[Col_Put][j] == temp_tile_color ) {
				   temp_col = Col_Put;
				   temp_row = j;
				   break; 
				}
			}
			for (j = Row_Put-1; j >= temp_row; j--)
			   temp[Col_Put][j] = temp_tile_color;
	}
    // Taþ konan yerden sað yukarý çapraza bak
	if ( ((*State_Data)[Col_Put+1][Row_Put-1] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put-1] != empty)  ) {
		for (i = Col_Put+1; i <= Board_Size-1; i++) {
			for (j = Row_Put-1; j >= 0; j--) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = Board_Size-1;
				   break; 
				}
			}
		}
		j = Row_Put-1;
		for (i = Col_Put+1; i <= temp_col; i++) {
			if(j >= temp_row)
			   temp[i][j] = temp_tile_color;
			j--;
		}		 
	}
        // Taþ konan yerden saða bak
	if ( ((*State_Data)[Col_Put+1][Row_Put] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put] != empty)  ) {
		for (i = Col_Put+1; i <= Board_Size-1; i++) {
				if ((*State_Data)[i][Row_Put] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = Row_Put;
				   break; 
				}
		}
		for (i = Col_Put+1; i <= temp_col; i++) {
			   temp[i][Row_Put] = temp_tile_color;
		}		 
	}
    // Taþ konan yerden sað alt çapraza bak
	if ( ((*State_Data)[Col_Put+1][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put+1][Row_Put+1] != empty)  ) {
		for (i = Col_Put+1; i <= Board_Size-1; i++) {
			for (j = Row_Put+1; j <= Board_Size-1; j++) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = Board_Size-1;
				   break; 
				}
			}
		}
		j = Row_Put+1;
		for (i = Col_Put+1; i <= temp_col; i++)
		{
			if(j <= temp_row)
			   temp[i][j] = temp_tile_color;
			j++;

		}
	}
    // Taþ konan yerden  aþaðýya bak
	if ( ((*State_Data)[Col_Put][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put][Row_Put+1] != empty)  ) {
			for (j = Row_Put+1; j <= Board_Size-1; j++) {
				if ((*State_Data)[Col_Put][j] == temp_tile_color ) {
				   temp_col = Col_Put;
				   temp_row = j;
				   break; 
				}
			}
			for (j = Row_Put+1; j <= temp_row-1; j++) {
               temp[Col_Put][j] = temp_tile_color;
			}
	}
    // Taþ konan yerden sol aþaðý çapraza bak
	if ( ((*State_Data)[Col_Put-1][Row_Put+1] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put+1] != empty)  ) {
		for (i = Col_Put-1; i >= 0; i--) {
			for (j = Row_Put+1; j <= Board_Size; j++) {
				if ((*State_Data)[i][j] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = j;
				   i = 0;
				   break; 
				}
			}
		}
		j = Row_Put+1;
		for (i = Col_Put-1; i >= temp_col; i--)
		{
			if (j<=temp_row)
			   temp[i][j] = temp_tile_color;
			j++;
		}		 
	}

	     // Taþ konan yerden sola bak
	if ( ((*State_Data)[Col_Put-1][Row_Put] != temp_tile_color) && ((*State_Data)[Col_Put-1][Row_Put] != empty)  ) {
		for (i = Col_Put-1; i >= 0; i--) {
				if ((*State_Data)[i][Row_Put] == temp_tile_color ) {
				   temp_col = i;
				   temp_row = Row_Put;
				   break; 
				}
		}
		for (i = Col_Put-1; i >= temp_col; i--) {
			   temp[i][Row_Put] = temp_tile_color;
		}		 
	}
	*/

	for (int i = 0; i <= Board_Size-1; i++)
		for (int j = 0; j <= Board_Size-1; j++)
		  (*State_Data)[i][j] = temp[i][j];
}
//HASAN
/*
Evaluates the given game state and returns an integer
*/
int evaluateGameState(int _State_Data[Board_Size][Board_Size],int moveNum, bool playersTurn)
{
int result=0;
int sWeight=0;
int tileDiff=0,tileDiffA=0,tileDiffB=0;
int mobilityDiff=0,mobilityA=0,mobilityB=0;
int coeffSquareWeight=100;
int coeffMaxTile, coeffMaxMobility;


//if computer's turn evaluate state considering white tiles
if(playersTurn==false) {
	//evaluate square weight component
	for(int i=0; i<Board_Size; i++) {
		for(int j=0; j<Board_Size; j++) {
			if(_State_Data[i][j]==white) {
				sWeight=sWeight + squareWeight[i][j];
			}
		}
	}
	//evaluate maximize tiles component
	for(int i=0; i<Board_Size; i++) {
		for(int j=0; j<Board_Size; j++) {
			if(_State_Data[i][j]==white){
				tileDiffA=tileDiffA+1;
			}
			if(_State_Data[i][j]==black){
				tileDiffB=tileDiffB+1;
			}
		}
	}
	tileDiff=tileDiffA-tileDiffB;
	//evaluate maximize mobility component
	/*
		beyaz ve siyah için possible move hesaplamaliyiz!!
	*/
	mobilityDiff=mobilityA-mobilityB;
}
//if player's turn evaluate considering black tiles
else {
	//evaluate square weight component
	for(int i=0; i<Board_Size; i++) {
		for(int j=0; j<Board_Size; j++) {
			if(_State_Data[i][j]==black) {
				sWeight=sWeight + squareWeight[i][j];
			}
		}
	}
	//evaluate maximize tiles component
	for(int i=0; i<Board_Size; i++) {
		for(int j=0; j<Board_Size; j++) {
			if(_State_Data[i][j]==black){
				tileDiffA=tileDiffA+1;
			}
			if(_State_Data[i][j]==white){
				tileDiffB=tileDiffB+1;
			}
		}
	}
	tileDiff=tileDiffA-tileDiffB;
	//evaluate maximize mobility component
	/*
		beyaz ve siyah için possible move hesaplamaliyiz!!
	*/
	mobilityDiff=mobilityA-mobilityB;
}
//calculate coefficients for tileDiff and mobilityDiff
if(moveNum<50) {
	coeffMaxTile=1;
}
else {
	coeffMaxTile=10;
}
if(moveNum<50) {
	coeffMaxMobility=1*moveNum;
}
else {
	coeffMaxMobility=50;
}
result=coeffSquareWeight*sWeight + coeffMaxTile*tileDiff + coeffMaxMobility*mobilityDiff;
return result;

}
