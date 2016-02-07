def run_correctness_tests
  compile_command = "g++ -std=c++11 -Ofast test.cpp ahocorasick.cpp karprabin.cpp"
  system(compile_command)
  output = `./a.out`

  if output.include? "FAIL"
    puts output
    puts "Correctness tests failed. Failures above."
  else
    puts "Correctness tests completed successfully."
  end
end

run_correctness_tests if ARGV.include? "c"
run_performance_tests if ARGV.include? "p"
