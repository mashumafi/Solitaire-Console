#pragma once

#include <Piece.hpp>

#include <vector>

class Grid
{
public:
  virtual ~Grid();
  void addPiece(Piece*);
  void addPiece(std::string);
private:
  std::vector<Piece*> pieces;
};
