# Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

g++ lib1.cpp -shared -o lib1.so
g++ main.cpp -L. -l1 -o main