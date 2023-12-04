#include "./../include/shapes.h"

ClockPixel digitShapes[10][5][3] = {
    {
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR}
    },
    {
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR}
    },
    {
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, INVIS},
            {COLOR, COLOR, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
    },
    {
            {COLOR, INVIS, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, INVIS},
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, INVIS},
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
            {INVIS, INVIS, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
    },
    {
            {COLOR, COLOR, COLOR},
            {COLOR, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
            {INVIS, INVIS, COLOR},
            {COLOR, COLOR, COLOR},
    }
};

ClockPixel colonShape[5][3] = {
        {INVIS, INVIS, INVIS},
        {INVIS, COLOR, INVIS},
        {INVIS, INVIS, INVIS},
        {INVIS, COLOR, INVIS},
        {INVIS, INVIS, INVIS},
};

ClockPixel (*getClockDigit(unsigned int digit))[3]{
    return digitShapes[digit];
}

ClockPixel (*getClockColon())[3]{
    return colonShape;
}