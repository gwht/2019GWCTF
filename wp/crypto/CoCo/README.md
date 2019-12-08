## CoCo
这道题本来想出难一点的lfsr，结果弟弟自己都做不出，最后还是拿了0ctf的lfsr那题改成了在多项式的形式下进行运算，其实看懂了整个过程以后就会发现直接用当初0ctf的脚本跑就能出（捂脸，wtcl  
```python
# -*- coding:utf8 -*-
from z3 import *
from Crypto.Util.number import long_to_bytes
import hashlib

def combine(x1, x2, x3):
    return (x1*x2)^(x2*x3)^(x3*x1)

def solve_3_lfsr(keystream, relevant_bit_indices, length, mask_length):
    len_mask = (2 ** (mask_length + 1) - 1)
    result_bits = map(long, "".join([bin(ord(c))[2:].zfill(8) for c in keystream]))
    s = Solver()
    x = BitVec('x', length)  
    y = BitVec('y', length)  
    z = BitVec('z', length)
    inits = [x, y, z]
    for result in result_bits:
        combs = []
        new_inits = []
        for index in range(3):  # 无符号数的移位需要使用LShR，表示逻辑移位
            relevant_bit1 = (inits[index] & (1 << relevant_bit_indices[index][0]))
            bit1_value = LShR(relevant_bit1, relevant_bit_indices[index][0])
            relevant_bit2 = inits[index] & (1 << relevant_bit_indices[index][1])
            bit2_value = LShR(relevant_bit2, relevant_bit_indices[index][1])
            single_lfsr_result = bit1_value ^ bit2_value
            combs.append(single_lfsr_result)
            new_init = ((inits[index] << 1) & len_mask) ^ single_lfsr_result
            new_inits.append(new_init)
        s.add(combine(combs[0], combs[1], combs[2]) == result)  # 约束条件
        inits = new_inits
    s.check()
    model = s.model()
    x_res = int(str(model[x]))
    y_res = int(str(model[y]))
    z_res = int(str(model[z]))
    return x_res, y_res, z_res

with codecs.open("keystream", 'rb', 'utf8') as input_file:
    data = input_file.read()
    mask1 = (42, 26)
    mask2 = (35, 13)
    mask3 = (47, 22)
    keystream = data[:24]
    x, y, z = solve_3_lfsr(data[:24], [mask1, mask2, mask3], 48, 48)
    init1, init2, init3 = map(long_to_bytes, [x, y, z])
    print "GWHT{" + hashlib.md5(init1 + init2 + init3).hexdigest() + "}"
```