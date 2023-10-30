FROM python:3.11-alpine AS RUN_STAGE

RUN apk add --no-cache g++ && pip3 install matplotlib

COPY . .

RUN g++ sorting_algorithms.cpp -std=c++11 -DWITHOUT_NUMPY -I /usr/local/include/python3.11 -lpython3.11 -o sorting_algorithms  && \
    ./sorting_algorithms

FROM scratch AS export-stage
COPY --from=RUN_STAGE out.jpg .
COPY --from=RUN_STAGE Out-sizes.jpg .

