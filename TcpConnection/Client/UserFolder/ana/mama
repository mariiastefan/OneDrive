#include "Board.h"

const char kEmptyBoardCell[] = "____";

const std::optional<Piece>& Board::operator[](const Position& position) const
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw "Board index out of bound.";

	return m_pieces[line * kWidth + column];
}

std::optional<Piece>& Board::operator[](const Position& position)
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw "Board index out of bound.";

	return m_pieces[line * kWidth + column];
}

std::ostream & operator<<(std::ostream & os, const Board & board)
{
	Board::Position position;
	auto&[line, column] = position;

	for (line = 0; line < Board::kHeight; ++line)
	{
		for (column = 0; column < Board::kWidth; ++column)
		{
			if (board[position])
				os << *board[position];
			else
				os << kEmptyBoardCell;	// TODO: change this to invalid piece, when possible
			os << ' ';
		}
		os << std::endl;
	}

	return os;
}
