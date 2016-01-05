//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef ReversiH
#define ReversiH
                     
# define Board_Size 8
# define Cell_Height_Width 50
# define NULL 0

//---------------------------------------------------------------------------
#include "Game_State.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TDrawGrid *Game_Board;
	TMemo *Memo_Designer_Interface;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Game_BoardClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
void Initialize_GUI();
void Create_Initial_State();
void Visualize_Current_State();
void Calculate_Resulting_State(int (*State_Data)[Board_Size][Board_Size], int Col_Put, int Row_put);
int evaluateGameState(int _State_Data[Board_Size][Board_Size],int moveNum, bool playersTurn);
#endif
