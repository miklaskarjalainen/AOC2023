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
        return (self.schematic[_idx], _idx)

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

    def get_numbers(self) -> [(int, [int])]:
        _nums = []
        _cur_num = -1

        _idx = 0
        _idxs = []

        for ch in self.schematic:
            # disables screenwrapping from end of a line
            if _idx % self.width == 0:
                if _cur_num != -1:
                    _nums.append((_cur_num, _idxs))
                    _idxs = []
                    _cur_num = -1

                
            if ch.isdigit():
                if _cur_num != -1:
                    _cur_num *= 10
                    _cur_num += int(ch)
                else:
                    _cur_num = int(ch)
                _idxs.append(_idx)
            else:
                if _cur_num != -1:
                    _nums.append((_cur_num, _idxs))
                    _idxs = []
                    _cur_num = -1
            
            _idx += 1
    
        return _nums

schematic = EngineSchematic.init_from_file("./input.txt")
nums = schematic.get_numbers()

stars = {} # <idx>: <nums>
for (num, idxs) in nums:
    print("", num, idxs)
    _found = False
    for idx in idxs:
        if _found:
            break
        for (n, n_idx) in schematic.get_neighbours_idx(idx):
            if n == "*":
                if n_idx in stars:
                    stars[n_idx].append(num)
                else:
                    stars[n_idx] = [num]
                _found = True
                break


result = 0
for k in stars.keys():
    nums = stars[k]
    if len(nums) == 2:
        result += nums[0] * nums[1]

print(str.format("Result: {}", result))