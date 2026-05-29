#include "aes_prng.h"

void SubBytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void ShiftRows(uint8_t state[4][4])
{
    // Сдвиг второй строки на 1
    uint8_t temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    // Сдвиг третьей строки на 2
    uint8_t temp1 = state[2][0];
    uint8_t temp2 = state[2][1];
    state[2][0] = state[2][2];
    state[2][1] = state[2][3];
    state[2][2] = temp1;
    state[2][3] = temp2;

    // Сдвиг четвертой строки на 3
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

void AddKey(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] ^= key[i][j];
        }
    }
}

AES_PRNG::AES_PRNG(const uint8_t seed[16])
{
    // Инициализируем состояние из seed
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = seed[i * 4 + j];
        }
    }
}

void AES_PRNG::generate(uint8_t output[16])
{
    for (int round = 0; round < 10; round++)
    {
        SubBytes(state);
        ShiftRows(state);
        AddKey(state);
    }
    // Копируем состояние в output
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            output[i * 4 + j] = state[i][j];
        }
    }
}