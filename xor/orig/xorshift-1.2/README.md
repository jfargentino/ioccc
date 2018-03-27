This archive contains the files related to my papers "An experimental
exploration of Marsaglia's xorshift generators, scrambled" and "Further
scramblings of Marsaglia's xorshift generators". The data generated during
the experiments is available as a separate download.

- The directory "full" contains all that is necessary to compute
  full-period generators using [Fermat](http://home.bway.net/lewis/). 

- The directory "data" contains scripts eval-01.rb and eval-db.rb, which
  analyze the results of TestU01/Dieharder and print a succint report of
  the test results. For example,

	./eval-01.rb test-xorshift64-small >xorshift64-small
  
  will produce data for SmallCrush on the xorshift64 generators.

  The script conj.sh can be used with xorshift data to get combined
  results for xorshift conjugate generators:

	./conj.sh <xorshift64-small

  The script ./sum.sh can instead be used to add values from standard
  and reverse generators. For instance,

	./eval-01.rb test-xorshift64star32-medium >xorshift64star32-medium
	./eval-01.rb test-xorshift64star32-medium-rev >xorshift64star32-medium-rev
	./sum.sh xorshift64star32-medium xorshift64star32-medium-rev >xorshift64star32-medium-comb

- In the the directory "c" for each GENERATOR you can find

	* GENERATOR.c : used to create the TestU01 and the stdout version.
	* GENERATOR-ed.c : computes equidistribution
	* GENERATOR-ez.c : computes the escape-from-zero statistics

  compile.sh compiles all binaries, except for those computing equidistribution,
  as they require [MTToolBox](https://github.com/MSaito/MTToolBox/). The libraries
  associated with TestU01 must be installed and accessible (compile.sh assumes,
  however, that includes might be in /usr/local/include).
  
- In the the directory "c/speed" you can find speed tests.

- The directory "dieharder" contains a CHANGES file and an additional source by
  which you can get the modified version of Dieharder used to perform the
  tests, starting from Dieharder 3.31.1.

- The directory "equidist" contains files describing the equidistribution
  score of each xorshift generator considered in the paper.
