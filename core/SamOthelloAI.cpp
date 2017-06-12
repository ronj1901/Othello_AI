#include <ics46/factory/DynamicFactory.hpp>
#include "SamOthelloAI.hpp"
#include  "OthelloCell.hpp"
#include <iostream>
#include  <limits>



ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, shambhut::MyOthelloAI, "SAM's OTHELLO AI(required)");


std::pair<int, int> shambhut::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    // implementation of my AI goes here
	isBlack = state.isBlackTurn();

	int current;
	int best = -10000000;
	std::pair<int,int> bestMove(1,1);

	std::unique_ptr<OthelloGameState> temp = state.clone();

	std::vector<std::pair<int, int>> newMoves = moves(temp);

 	for( auto i  : newMoves) {

 		//std::cout << i.first << " " << i.second << "\n";

 		std::unique_ptr<OthelloGameState> tempGS = state.clone();

 		tempGS->makeMove(i.first, i.second);

 		//check whose turn
 		//decide min or max to pick

 		current  = search(tempGS, 0);
 		if(current > best){
 			best = current;
 			bestMove = i;
 		}
 	}

return bestMove;

}



 std::vector<std::pair<int,int>> shambhut::  MyOthelloAI  :: moves(std::unique_ptr<OthelloGameState> & GS) {

 		std::vector<std::pair<int, int>> possibleMoves;   // generate all possible moves for fiven game stte

 		for (int i =0; i < GS->board().width(); ++i) {

 			for(int j = 0; j < GS->board().height() ; ++j){

 				if( GS->isValidMove(i, j) ){
 					possibleMoves.push_back(std::pair<int, int>(i,j));
 				}

 			}
 		}


 		return possibleMoves;

 }


 int shambhut::MyOthelloAI:: search(std::unique_ptr<OthelloGameState> & GS, int depth) {


 	bool initialized = false;
 	int best =0;
 	int current = 0;
 	int DEPTH_LIMIT =  4;



 	if(GS->isGameOver()){
 		return evaluate(GS);
 	}
 	if(DEPTH_LIMIT == depth){
 		return evaluate(GS);
 	}

 	std::vector<std::pair<int, int>> newMoves = moves(GS);

 	

 	for( auto i  : newMoves) {
 		std::unique_ptr<OthelloGameState> tempGS = GS->clone();

 		tempGS->makeMove(i.first, i.second);

 		 current  = search(tempGS, depth+1);

 		 if(!initialized){
 		 	best = current;
 		 	initialized = true;
 		 }
 		 else if (isBlack == GS->isBlackTurn() ) {
 		 	 if ( current > best) {
 		 	 	 best = current;
 		 	 }
 		 } else{
 		 	if ( current < best) {
 		 	 	 	best = current;
 		 	  }
 		 }

 	}


return best;



 }

int shambhut::MyOthelloAI::evaluate(std::unique_ptr<OthelloGameState> &GS){

	int width =  GS->board().width();
	int height  =  GS->board().height();
	
	int G[width][height];

	int heuristicValue  = 0;



	G[0][0] =  20;
	G[height-1][0] = 20;
	G[0][width-1]  = 20;
	G[height-1][width-1] = 20;

				

	 
	if  ( GS->board().cellAt(0,0) == OthelloCell:: black ) {
			heuristicValue +=  G[0][0];

	}

	else {
		heuristicValue -=  G[0][0];
	}


	if  ( GS->board().cellAt(height-1,0) == OthelloCell:: black ) {
			heuristicValue +=  G[height-1][0];

	}

	else {
		heuristicValue -=  G[height-1][0];
	}


	if  ( GS->board().cellAt(0,width-1) == OthelloCell:: black ) {
			heuristicValue +=  G[0][width-1];

	}

	else {
		heuristicValue -=  G[0][width-1];
	}


	if  ( GS->board().cellAt(height-1,width-1) == OthelloCell:: black ) {
			heuristicValue +=  G[height-1][width-1];

	}

	else {
		heuristicValue -=  G[height-1][width-1];
	}



 				
	// for (int i =0; i < GS->board().width(); ++i) {

 // 			for(int j = 0; j < GS->board().height() ; ++j){

 // 				if  ( GS->board().cellAt(i,j) ==  OthelloCell:: black ) {
 // 					heuristicValue +=  V[i][j];


 // 				}
 // 				else if ( GS->board().cellAt(i,j) ==  OthelloCell::white){
 // 					heuristicValue -= V[i][j];

 // 				}

 // 			}

 // 	}


 	int result  = 25 * ( GS->blackScore() - GS->whiteScore() ) + heuristicValue * 100;

	// int combinedScore =  GS->blackScore() + GS->whiteScore();
	// int blackHeuritic =   100 * (GS->blackScore() - GS->whiteScore()) / combinedScore;
	// int whiteHeuristic =    100 *(-GS->blackScore() + GS->whiteScore()) / combinedScore;


	if (isBlack){

		
		return  result ;
	}
	else{
	
		return -result;
	}

}