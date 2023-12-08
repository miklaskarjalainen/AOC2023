import card

when isMainModule:
  var cardScore: seq[int] = @[]
  let cards = parse_file("./input.txt")
  
  # Gather the how many additional copies each card gives us
  for c in cards:
    cardScore.add(c.getWinningNumberCount())
  
  # recursive function to count each copy
  proc countCopies(idx: int): int =
    var count = 1

    for i in 1..(cardScore[idx]):
      count += countCopies(idx + i)
    
    return count

  # loop through each card
  var scratchCardCount = 0
  for idx in 0..(cardScore.len()-1):
    scratchCardCount += countCopies(idx)

  echo "Result: ", $cardScore
  echo "totalCopies: ", $scratchCardCount