#!/usr/bin/env ruby

input_path = ARGV[0]
output_path = ARGV[1]

raise "Usage: codegen.rb [DICTIONARY] [TARGET]" if output_path.nil?

writeFd = File.new(output_path, 'w')
readFd = File.open input_path
writeFd.write <<~EOF
const char *dictionary[] = {
EOF

readFd.readlines.each do |line|
  tuple = line.strip.split "\t"
  word = tuple[1]
  writeFd.write "  \"#{word}\",\n"
end
writeFd.write "};\n"
writeFd.close
