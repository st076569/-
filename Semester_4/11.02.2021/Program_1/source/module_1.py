#################################################################################
# "Расстояние Левенштейна". Есть  цех с конвейерным производством. Конвейр      #
# состоит из N типовых блоков установленных на ленту конвейера. Блоки бывают    #
# одного из K типов. В рамках перепрофилирования цех решили переоборудовать     #
# так, чтобы конвейер состоял из M блоков того же типа. Определить минимальную  #
# стоимость переоборудования, если дана информация о стоимости работы для       #
# каждого типа блока:                                                           #
# 1) Добавления Ai;                                                             #
# 2) Удаление Di;                                                               #
# 3) Замена блока типа i на j - Cij;                                            #
# И информация об устройстве конвейера до и после работ(в удобной вам форме)    #
#################################################################################

# Границы стоимости операций (для Ai, Di, Cij)
MAX_COST = int(100)
MIN_COST = int(0)

# Границы количества типов блоков (для K)
MAX_VARY = int(100)
MIN_VARY = int(2)

# Границы количества блоков на конвейере (для M, N)
MAX_LENGTH = int(100)
MIN_LENGTH = int(1)

########## def scanInt ##########################################################
# Читает входное значение x типа int, x in [min, max]                           #
#################################################################################

def scanInt(min, max):

    # Вводим новое значение
    tempInt = int(input())
    
    # Проверяем на выход за границы диапазона
    if (tempInt < min or tempInt > max):
        raise ValueError("inappropriate argument value of int() type")
    else:
        return tempInt

########## def scanValue ########################################################
# Читает входное значение x типа int, x in [min, max]                           #
#################################################################################

def scanValue(name, min, max):

    # Вспомогательные переменные
    haveRead  = bool(False)
    tempValue = int(0)
        
    # Чтение значения tempCost
    while not haveRead:
        print("Input", name, "(int() in [", min, ",", max, "]) :")
        try:
            tempValue = scanInt(min, max)
        except (Exception) as e:
            print("Error :", e, "\n")
        else:
            haveRead = True
    
    # Возвращаем стоимость
    return tempValue

########## def scanWord #########################################################
# Читает список "букв" из определенного алфавита.                               #
#################################################################################

def scanWord(word, vary, num):

    # Считываем длину слова "num"
    length = scanValue("config" + str(num) + " length", MIN_LENGTH, MAX_LENGTH)

    # Считываем само слово
    for i in range(length):
        word.append(scanValue("element" + str(i), 0, vary - 1))


########## class Data ###########################################################
# Хранит входные данные задачи                                                  #
#################################################################################

class Data:

    # Стоимости операций
    addValue    = int(0)
    deleteValue = int(0)
    changeValue = int(0)

    # Информация об устройстве конвейера до и после переоборудования
    startConfig = []
    endConfig   = []

########## class LowensteinSolver ###############################################
# Решает задачу поиска расстояния Левенштейна                                   #
#################################################################################

class LowensteinSolver:

    # Информация о конфигурациях и таблице наименьших стоимостей
    __info      = Data()
    __startLine = []
    __endLine   = []
    __table     = []

    # Считывает входные данные
    def scanInformation(self):
        
        # Чтение стоимости добавления, удаления, замены
        self.__info.addValue = scanValue("'add' cost", MIN_COST, MAX_COST)
        self.__info.deleteValue = scanValue("'delete' cost", MIN_COST, MAX_COST)
        self.__info.changeValue = scanValue("'change' cost", MIN_COST, MAX_COST)

        # Чтение количества различных типов оборудования
        typesNumber = scanValue("types number", MIN_VARY, MAX_VARY)

        # Чтение начальной и конечной конфигураций оборудования
        scanWord(self.__info.startConfig, typesNumber, 1)
        scanWord(self.__info.endConfig, typesNumber, 2)

    # Выводит входные данные
    def printData(self):

        # Стоимости операций
        print("\nCosts ('add', 'delete', 'change') :", self.__info.addValue,
              self.__info.deleteValue, self.__info.changeValue)

        # Начальная и конечная конфигурации оборудования
        print("Start configuration               :", self.__info.startConfig)
        print("End   configuration               :", self.__info.endConfig)

    # Инициализирует таблицу наименьших стоимостей
    def prepareTable(self):

        # Список последних символов начального слова
        self.__startLine.append(int(0))
        self.__startLine.extend(self.__info.startConfig)

        # Список последних символов последнего слова
        self.__endLine.append(int(0))
        self.__endLine.extend(self.__info.endConfig)

        # Таблица наименьших стоимостей
        for i in range(len(self.__endLine)):
            self.__table.append(list())
            for j in range(len(self.__startLine)):
                self.__table[i].append(int(0))
                if (i == 0):
                    self.__table[i][j] = int(j * self.__info.deleteValue)
            self.__table[i][0] = int(i * self.__info.addValue)

    # Возвращает стоимость при подходе к точке сверху
    def tryAdd(self, i, j):
        return self.__table[i - 1][j] + self.__info.addValue

    # Возвращает стоимость при подходе к точке слева
    def tryDelete(self, i, j):
        return self.__table[i][j - 1] + self.__info.deleteValue

    # Возвращает стоимость при подходе к точке по диагонали
    def tryChange(self, i, j):
        if (self.__startLine[j] == self.__endLine[i]):
            return self.__table[i - 1][j - 1]
        else:
            return self.__table[i - 1][j - 1] + self.__info.changeValue

    # Возвращает наименьшую стоимость смены конфигурации в точке (i, j)
    def computeMinCost(self, i, j):
        return min(self.tryAdd(i, j), self.tryDelete(i, j),
                   self.tryChange(i, j))

    # Заполняет таблицу наименьшими стоимостями
    def fillTable(self):
        for i in range(len(self.__info.endConfig)):
            for j in range(len(self.__info.startConfig)):
                self.__table[i + 1][j + 1] = self.computeMinCost(i + 1, j + 1)

    # Выводит содержимое таблицы наименьших стоимостей на экран
    def printTable(self):

        # Выводит содержимое таблицы
        print("\nOptimal costs :")
        for i in range(len(self.__table)):
            print(self.__table[i])

        # Выводит минимальную стоимость переоборудования (расст-е Левенш-на)
        iMax = len(self.__info.endConfig)
        jMax = len(self.__info.startConfig)
        print("\nMin cost :", self.__table[iMax][jMax])
