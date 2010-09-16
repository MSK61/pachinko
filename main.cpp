/************************************************************
 *
 * Copyright 2010 Mohammed El-Afifi
 *
 * pachinko is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pachinko is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pachinko.  If not, see <http://www.gnu.org/licenses/>.
 *
 * file:         main.cpp
 *
 * function:     main (complete program listing in this file)
 *
 * description:  calculates the best score among all routes
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  KDevelope 3.5.4, Fedora release 10 (Cambridge)
 *
 * notes:        This is a private program.
 *
 ************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream>
#include <stdlib.h>
#include <vector>

using std::vector;
typedef vector< unsigned short int > NailRow;
namespace
{
    // This's the quick recursive approach. A better iterative approach is to
    // accumulate the tree starting with leaves and moving towards the root,
    // effectively reducing the rows of nails, until we get the maximum score at
    // the root. This avoids calculating the maximum score starting at a
    // specific nail several times.
    /**
     * @brief Calculates the maximum sum of all routes
     *
     * @param nails    triangle of nails to calculate the partial maximum sum
     *                 for
     * @param row      row containing the nail to start with
     * @param idxInRow index of the nail to start with in the provided row
     * @return         the maximum sum among all routes starting with the given
     *                 nail
     */
    const unsigned long getMaxScore(
        const vector< NailRow >& nails, unsigned short int row,
        unsigned short int idxInRow)
    {
        const unsigned short int nextRow = row + 1;

        if (row == nails.size()) return 0;// number of rows exceeded

        return nails[row][idxInRow] +
               std::max(getMaxScore(nails, nextRow, idxInRow),
                        getMaxScore(nails, nextRow, idxInRow + 1));

    }
}

int main(int argc, char *argv[])
{
    unsigned short int curNail;
    unsigned short int curRow = 0;
    // I/O files
    static const char inFileName[] = "pachinko.in";
    std::ifstream inFile(inFileName);
    static const char outFileName[] = "pachinko.out";
    std::ofstream outFile(outFileName);
    vector< NailRow > nails;
    unsigned short int r;// number of nail rows
    unsigned short int rowSize;

    /// Read the problem description.
    inFile >> r;
    nails.resize(r);

    for (; curRow < r; curRow = rowSize)
    {

        rowSize = curRow + 1;
        nails[curRow].resize(rowSize);

        for (curNail = 0; curNail < rowSize; curNail++)
            inFile >> nails[curRow][curNail];

    }

    inFile.close();
    /// Save the result.
    outFile << getMaxScore(nails, 0, 0);
    outFile.close();
    return EXIT_SUCCESS;
}
