import card

when isMainModule:
  let cards = parse_file("./input.txt")
  var result = 0
  for c in cards:
    let s = c.getScore()
    echo $c, "score = ", $c.getScore()
    result += s
  
  echo "Result: ", $result