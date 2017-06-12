

#ifndef SAMOTHELLOAI_H
#define SAMOTHELLOAI_H

#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include  <vector>


namespace shambhut
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);

        //eval function  : main core for Othello AI

        int evaluate(std::unique_ptr<OthelloGameState> &GS);

        //Search function: Recursive 

       	int search(std::unique_ptr<OthelloGameState> & GS, int depth);


        //generate moves

        std::vector<std::pair<int, int>> moves(std::unique_ptr<OthelloGameState> & GS);


        bool isBlack;

        int V[8][8]{
        {20, -3, 11, 8, 8, 11, -3, 20},
    	{-3, -7, -4, 1, 1, -4, -7, -3},
    	{11, -4, 2, 2, 2, 2, -4, 11},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{8, 1, 2, -3, -3, 2, 1, 8},
    	{11, -4, 2, 2, 2, 2, -4, 11},
    	{-3, -7, -4, 1, 1, -4, -7, -3},
		{20, -3, 11, 8, 8, 11, -3, 20}};

    };
}


#endif
