#include <Grid.hpp>

using namespace std;

void Grid::addPiece(string s)
{
  pieces.push_back(new Piece(s));
}

void Grid::addPiece(Piece* p)
{
  pieces.push_back(p);
}

Grid::~Grid()
{
}
