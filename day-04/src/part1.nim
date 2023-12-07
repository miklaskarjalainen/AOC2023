import std/strutils
import std/strformat

type
  # 
  Card = ref object
    id: uint16
    winning_numbers: seq[int]
    playing_nums: seq[int]

proc `$`(card: Card): string =
  var output = fmt"Card {card.id}: "
  for num in card.winning_numbers:
    output.add(fmt"{num} ")
  output.add("| ")
  for num in card.playing_nums:
    output.add(fmt"{num} ")
  return output

proc parse_text(card: Card, line: string) = 
  # 'Card <num>: <winning-nums> | <playing-nums>\r"
  var line = line.replace("\r", "")
  line.removePrefix("Card ")
  
  # ID
  let end_pos = line.find(':') - 1
  card.id = cast[uint16](line[0..end_pos].replace(" ", "").parseUInt())

  # Winning nums
  let nums = line[end_pos+2..^1].split('|')

  let winnings_nums = nums[0].split(' ')
  for num in winnings_nums:
    let num = num.replace(" ", "")
    if num.len == 0:
      continue
    card.winning_numbers.add(num.parseInt())

  let playing_nums = nums[1].split(' ')
  for num in playing_nums:
    let num = num.replace(" ", "")
    if num.len == 0:
      continue
    card.playing_nums.add(num.parseInt())

proc parse_file(filepath: string): seq[Card] =
  var cards: seq[Card] = @[]

  let contents: string = readFile(filepath)
  let lines: seq[string] = contents.split("\n")
  for line in lines:
    if not line.startsWith("Card "):
      continue

    let c = Card(id: 0, winning_numbers: @[], playing_nums: @[])
    c.parse_text(line)
    cards.add(c)

  return cards

proc getScore(card: Card): int =
  const Scores: array[13, int] = [0,1,2,4,8,16,32,64,128,256,512,1024,2048]
  
  var score = 0 # idx
  for num in card.playing_nums:
    if card.winning_numbers.contains(num):
      score += 1

  return Scores[score]


when isMainModule:
  let cards = parse_file("./input.txt")
  var result = 0
  for c in cards:
    let s = c.getScore()
    echo $c, "score = ", $c.getScore()
    result += s
  
  echo "Result: ", $result