def read():
    filepath = '../src/input.hpp'
    PRINTER  = []
    with open(filepath, 'rt') as f:
        lines    = []
        location = []
        ls = 0
        for line in f:
            lines.append(line.rstrip('\n'))
        for vect in lines:
            location.append(vect.find("PRINTER"))
        for i in range(0, len(location)):
            if location[i] != -1:
                ls = i

    locsT = []
    locsT.append(lines[ls].find("true"))
    if locsT[0] != -1:
        for i in range(0, 4):
            if locsT[i] == -1:
                break
            else:
                locsT.append(lines[ls].find("true", locsT[i]+1))


    locsF = []
    locsF.append(lines[ls].find("false"))
    if locsF[0] != -1:
        for i in range(0, 4):
            if locsF[i] == -1:
                break
            else:
                locsF.append(lines[ls].find("false", locsF[i]+1))

    len_T = len(locsT)
    len_F = len(locsF)
    i, j = 0, 0
    while i < len_T and j < len_F:
        if locsT[i] != -1 and locsT[i] < locsF[j] or locsF[j] == -1 and locsT[i] != -1:
            PRINTER.append(True)
            i += 1
        elif locsF[j] != -1 and locsF[j] < locsT[i] or locsT[i] == -1 and locsF[j] != -1:
            PRINTER.append(False)
            j += 1
        else:
            i += 1
            j += 1
    f.close()
    return PRINTER
