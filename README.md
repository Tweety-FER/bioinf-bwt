# Dynamic Suffix Array Implementation

This repository contains an implementation of the dynamic suffix array described in the paper [**A four-stage algorithm for updating a Burrows-Wheeler transform**](http://ac.els-cdn.com/S0304397509004770/1-s2.0-S0304397509004770-main.pdf?_tid=611f5686-ba92-11e5-a58c-00000aacb362&acdnat=1452757536_6f7caedbc51814202a7ba1b0595f3cb6) by Salson et al. It was implemented as a project assignment for our [Bioinformatics course](http://www.fer.unizg.hr/predmet/bio).

## Dependencies

We are using [Gerlach's implentation](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.132.468&rep=rep1&type=pdf) of [Mäkinen and Navarro’s dynamic structures](http://dl.acm.org/citation.cfm?id=1367072). This allows us to perform our *rank<sub>c</sub>*, *insert* and *delete* operations in O(log n log &sigma;), where *n* is the length of the text and *&sigma;* is the size of the alphabet &Sigma;. These structures also include a sampler, which we are using for (more) efficient computation of ISA values at a given index.

## Relevant files

The majority of our implementation is contained within the header file *DynamicSuffixArray.h* and its implementation *DynamicSuffixArray.cpp*. The class, variable and method comments are all contained within the header file. The comments inside the C++ file only explain the implementation details or reference the paper.

The rest of the C++ files are unchanged or mostly unchanged, having required at most a few (re)definitions to satisfy our compilers.

The building process is managed by the *Makefile*. It manages the building process, as well as the compiler options and flags. The building can simply be started by running

```bash
make
```

or

```bash
make all
```

## Running the examples

For testing purposes we implemented unit tests using [Catch automated test framework](http://catch-lib.net). Tests are grouped into categories that can be run independently.
To start all tests use:
```bash
./test
```
To start all tests with time monitoring options use:
```bash
./test -d yes
```
To print all possible options use:
```bash
./test -?
```

## Test results

Action | Length | Time[s] | Memory[MB]
-------|------|-------|-------
Calculate BWT | 1031 | 0.003357 | 1
Calculate BWT | 5385 | 0.028451 | 1
Calculate BWT | 35970 | 0.176832 | 1
Calculate BWT | 189561 | 1.214295 | 2
Calculate BWT | 2494862 | 21.097746 | 9
Adding string | 512 into 1032 | 0.001728 | 1
Deleting string | 512 from 1032 | 0.001916 | 1
Deleting string | 512 from 35970 | 0.002748 | 2
Adding string | 1413 into 189561 | 0.010186 | 2
Deleting string | 42000 from 189561 | 0.0203301 | 2
Deleting string | 126183 from 700918 | 0.738056 | 4
Adding string | 126183 into 700918 | 0.902695 | 4



