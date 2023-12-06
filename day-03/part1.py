
class EngineSchematic:
    schematic: str = ""
    width: int = -1
    height: int = -1

    def __init__(self, schematic: str):
        self.width = schematic.find("\n")
        self.height = schematic.count("\n") + 1
        self.schematic = schematic.replace("\n", "")
        print(str.format("Initialized width: {} height: {}", self.width, self.height))

    def init_from_file(filepath: str):
        schematic = ""
        
        f = open(filepath, "r")
        schematic = f.read()
        f.close()
        return EngineSchematic(schematic)

    def get_chr_idx(self, idx: int):
        return self.schematic[idx]

    def get_chr(self, x: int, y: int):
        _idx = y * self.width + x
        return self.schematic[_idx]

    def get_neighbours(self, x: int, y: int):
        _idx = y * self.width + x
        return self.get_neighbours_idx(_idx)

    def get_neighbours_idx(self, idx: int):
        _w = self.width
        _y = int(idx / _w)
        _x = int(idx % _w)

        _neighbours = []
        for _offx in range(-1,2):
            _new_x = _x + _offx
            if _new_x < 0:
                continue
            if _new_x >= self.width:
                continue

            for _offy in range(-1, 2):
                _new_y = _y + _offy
                if _offx == 0 and _offy == 0:
                    continue
                if _new_y < 0:
                    continue
                if _new_y >= self.height:
                    continue
                _neighbours.append(self.get_chr(_new_x, _new_y))

        return _neighbours

    def get_numbers(self) -> [(int, int)]:
        _nums = []
        _cur_num = -1
        _idx = 0
        _is_neg = False

        for ch in self.schematic:
            # disables screenwrapping from end of a line
            if _idx % self.width == 0:
                if _cur_num != -1:
                    _nums.append((_cur_num, _idx-1))
                    _cur_num = -1
                
            if ch.isdigit():
                if _cur_num != -1:
                    _cur_num *= 10
                    _cur_num += int(ch)
                else:
                    _cur_num = int(ch)
            else:
                if _cur_num != -1:
                    _nums.append((_cur_num, _idx-1))
                    _cur_num = -1
            
            _idx += 1
    
        return _nums


def countDigit(n) -> int: 
    count = 0
    n = abs(n)
    while n != 0: 
        n //= 10
        count += 1
    return count

schematic = EngineSchematic.init_from_file("./input-part1.txt")
nums = schematic.get_numbers()

result = 0
for (num, idx) in nums:
    _count = countDigit(num)
    _found = False
    for offset in range(0,_count):
        if _found:
            break
        
        _new_idx = idx - offset
        _y = int(idx / 140)
        _x = int(idx % 140)

        _neighbours = schematic.get_neighbours_idx(_new_idx)
        for n in _neighbours:
            if (not n.isdigit()) and n != ".":
                _found = True
                result += num

print(str.format("Result: {}", result))