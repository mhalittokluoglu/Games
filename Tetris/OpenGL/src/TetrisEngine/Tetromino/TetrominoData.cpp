#include "TetrominoData.hpp"
#include <cstring>

NearIndices::NearIndices()
{
    memset(X, 0, sizeof(X));
    memset(Y, 0, sizeof(Y));
    memset(Available, 0, sizeof(Available));
}