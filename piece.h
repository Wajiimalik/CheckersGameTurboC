#ifndef PIECE_H
#define	PIECE_H

#include "datastructures.h"


void DrawPiece(PtrBoard, PtrCell, int, int);

/* 
 * @description : Used to draw the piece, This can be called anywhere you need to draw a piece.
 * 
 * @param - board - Address of the global struct Board variable. We use it to 'fill' in the array entries, as we build the piece
 * @param - cell - Address of the cell to which this piece belongs
 * @param - pieceNo - Index of this piece in the Pieces array in Board struct
 * @param - Color used to draw this piece
 * 
 */

void DrawPiece(PtrBoard board, PtrCell cell, int pieceNo, int color)
{
    //Is this a red or blue piece ?
    PieceType type = color == RED ? Red : Black ;

    // configure the properties of associated cell
    cell->IsOccupied = 1;  //this cell now has a piece belonging to it.
    cell->OccupiedBy = type;

    board->Pieces[pieceNo].IsKing = 0;
    board->Pieces[pieceNo].State = OnBoard;
    board->Pieces[pieceNo].Type = type;
    
    board->Pieces[pieceNo].ID = pieceNo;

    //store a reference to this piece in cell
    cell->Piece = &board->Pieces[pieceNo];
    
    //set draw color of circle / piece
    setcolor(color);

    //center of circle; this is also used as seed point
    int circleX = (cell->Left  + cell->Right) / 2;
    int circleY = (cell->Top + cell->Bottom) / 2;

    //draws the circle for this piece
    circle( circleX ,circleY, RADIUS  );

    setfillstyle(SOLID_FILL, color);

    floodfill( circleX, circleY, color );
    
    // reset draw color to draw the next rectangle / cell
    setcolor(BLUE);
}

void MovePiece(PtrBoard board, PtrCell clickedCell , PtrCell clickedTarget, PtrCell target1, PtrCell target2, int turn)
{
    //change prev cell data
               
    clickedCell->IsOccupied = FALSE;

    //change target cell data

    clickedTarget->Piece = clickedCell->Piece;
    clickedTarget->IsOccupied = TRUE;

    clickedCell->Piece = NULL;

    //re draw prev cell

    DrawCell( clickedCell, clickedCell->Row, clickedCell->Column );

    //redraw target cells in normal white color

    if ( target1 != NULL) DrawCell( target1, target1->Row, target1->Column );
    if ( target2 != NULL) DrawCell( target2, target2->Row, target2->Column );

    //draw piece on target cell

    DrawPiece( board, clickedTarget, clickedTarget->Piece->ID, turn );

}

#endif	/* PIECE_H */

