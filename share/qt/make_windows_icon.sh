#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/greencoin.ico

convert ../../src/qt/res/icons/greencoin-16.png ../../src/qt/res/icons/greencoin-32.png ../../src/qt/res/icons/greencoin-48.png ${ICON_DST}
