$test_file = "english.50MB"

def run_correctness_tests
  compile_command = "clang++ -std=c++11 -Ofast test.cpp ahocorasick.cpp karprabin.cpp"
  system(compile_command)
  output = `./a.out`

  if output.include? "AC FAIL" or output.include? "Segmentation"
    puts output
    puts "Aho-Corasick correctness tests failed. Failures above."
  else
    puts "Aho-Corasick correctness tests completed successfully."
  end

  if output.include? "KR FAIL" or output.include? "Segmentation"
    puts output
    puts "Karp-Rabin correctness tests failed. Failures above."
  else
    puts "Karp-Rabin correctness tests completed successfully."
  end
end

def print_output
  prep, search = `./a.out #{$test_file}`.split("\n")
  puts "Preprocessing: #{prep} ms"
  puts "Search: #{search} ms"
end

def run_performance_tests
  puts "Running Aho-Corasick without fprofile..."
  compile_command = "g++ -std=c++11 -Ofast performance.cpp ahocorasick.cpp karprabin.cpp"
  system(compile_command)
  print_output

  puts "Running Aho-Corasick with fprofile-generate..."
  system("g++ -std=c++11 -fprofile-generate -Ofast performance.cpp ahocorasick.cpp karprabin.cpp")
  `./a.out #{$test_file}`

  puts "Compiling with fprofile-use..."
  system("g++ -std=c++11 -fprofile-use -Ofast performance.cpp ahocorasick.cpp karprabin.cpp")
  puts "Running actual program"
  print_output

  puts "Running Karp-Rabin without fprofile..."
  compile_command = "g++ -std=c++11 -Ofast performance.cpp ahocorasick.cpp karprabin.cpp"
  system(compile_command)
  print_output

  puts "Running Karp-Rabin with fprofile-generate..."
  system("g++ -std=c++11 -fprofile-generate -Ofast performance.cpp ahocorasick.cpp karprabin.cpp")
  `./a.out #{$test_file}`

  puts "Compiling with fprofile-use..."
  system("g++ -std=c++11 -fprofile-use -Ofast performance.cpp ahocorasick.cpp karprabin.cpp")
  puts "Running actual program"
  print_output
end

run_correctness_tests if ARGV.include? "c"
run_performance_tests if ARGV.include? "p"
