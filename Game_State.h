//---------------------------------------------------------------------------

#ifndef Game_StateH
#define Game_StateH
//---------------------------------------------------------------------------
#include "Reversi.h"

#define white 3
#define black 2
#define possible_move 1
#define empty 0
extern bool is_computers_turn;



class Game_State
{
	 private:
	 public:
            int Number_of_Possible_Moves;
			Game_State* Back_Pointer;
			int Data[Board_Size][Board_Size];
			int Cost;
			Game_State(int _Data[Board_Size][Board_Size], Game_State* _back_pointer, int _Cost, int _Number_of_Possible_Moves);
			/*Puzzle_State(data_struct* Puzzle_Data, int Puzzle_size, Puzzle_State* _back_pointer, int _priority);
			int Successors(Puzzle_State* _Puzzle_State[4]);
			int Calc_Number_of_Successors();
			bool Is_Equal(Puzzle_State* Check_State);
			int Calc_Manhattan_Distance();
			int Calc_Number_of_Misplaced();
			int Calc_Total_Cost();
              */
};
int Calculate_Possible_Moves(int (*State_Data)[Board_Size][Board_Size]);
bool Is_Potential_Cell(int (*State_Data)[Board_Size][Board_Size], int x, int y);
bool Check_Cell(int (*State_Data)[Board_Size][Board_Size],int i,int j,int oppn_color);




#endif
