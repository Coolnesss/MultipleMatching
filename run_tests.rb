def run_correctness_tests
  compile_command = "g++ -std=c++11 -Ofast test.cpp ahocorasick.cpp karprabin.cpp"
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

run_correctness_tests if ARGV.include? "c"
run_performance_tests if ARGV.include? "p"
