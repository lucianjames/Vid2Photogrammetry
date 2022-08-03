
from PyQt5.QtWidgets import *

import vid2photogrammetry

def main():
    app = QApplication([])
    window = QWidget()
    window.setWindowTitle("Vid2Photogrammetry")
    window.show()
    app.exec_()

if __name__ == '__main__':
    main()