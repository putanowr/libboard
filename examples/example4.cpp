/**
 * @file   example4.cpp
 * @author Sebastien Fourey (GREYC)
 *
 * @brief  Illustration of the use of Board, ShapeList and Group.
 *
 * This source code is part of the Board project, a C++ library whose
 * purpose is to allow simple drawings in EPS, FIG or SVG files.
 * Copyright (C) 2007 Sebastien Fourey <http://foureys.users.greyc.fr>
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Board.h"

using namespace LibBoard;

int main( int , char *[] )
{
  Board board;
  board.clear( Color(200,255,200) );

  board.setLineWidth(0.01);            // For Board drawing methods.
  Shape::setDefaultLineWidth(0.02);    // For all Shapes constructors.

  for ( double x = -20.0; x <= 20; x+= 1.0 )
    for ( double y = -20.0; y <= 20; y+= 1.0 ) {
      board << Dot(x, y, Color::Black );
      board.setPenColorRGBf( 1.0, 0.0, 0.0 );
      board.drawDot( x+0.2, y+0.2 );
    }
  
  Group g;
  g << Line( -5, 2, 5, 2, Color::Red )
    << Rectangle( -5, 2, 1, 4, Color::Null, Color::Blue )
    << Rectangle( 4, 2, 1, 4, Color::Null, Color::Blue )
    << Ellipse( 0, 0, 5, 2, Color::Red, Color::Null );

  Group g2(g);
  Group g3(g);
  g2.translate( 0, 6 );
  g3.translate( 0, -6 );

  Group f;
  f << g << g2 << g3;
  f.rotateDeg( 45.0 );
  board << f;

  ShapeList l;
  Circle c( 2, 5, 1.8, Color::Red, Color::Green );
  for ( int i = 0; i < 5; ++i ) {
    l << c.scale( 1, 0.5 );
  }
  for ( double x = -20, a = 0; x < 20 ; x += 4, a += 0.3 ) {
    board << l.rotated( a ).translate( x, 10 );
  }

  g.clear();

  Rectangle r1( 2, 2, 3, 1, Color::Black, Color::Null );
  Rectangle r2 = r1.translated( -8, -8 );
  for ( double alpha = 0; alpha < 2*M_PI; alpha += 0.2 ) {
    g << r1.rotated( alpha );
    board << r2.rotated( alpha, r2.topLeft() );
  }

  board.saveEPS( "example4.eps", Board::A4 );
  board.saveFIG( "example4.fig", Board::A4 );

  board.scaleToWidth(10,Board::UseLineWidth);
  board.saveSVG( "example4.svg", Board::BoundingBox, 0.0, Board::UCentimeter );
}
