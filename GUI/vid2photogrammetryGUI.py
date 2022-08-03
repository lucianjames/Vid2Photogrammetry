from PyQt5.QtWidgets import *
from PyQt5 import uic

import vid2photogrammetry

class Gui(QMainWindow):
    def __init__(self):
        ## Init and load the GUI ##
        super(Gui, self).__init__()
        uic.loadUi('testGui.ui', self)

        ### Define widgets ###
        # Input file
        self.inFileText = self.findChild(QLineEdit, 'inFileText')
        self.inFileTool = self.findChild(QToolButton, 'inFileTool')
        self.inFileTool.clicked.connect(self.inFileToolClicked)
        # Output folder
        self.outFolderText = self.findChild(QLineEdit, 'outFolderText')
        self.outFolderTool = self.findChild(QToolButton, 'outFolderTool')
        self.outFolderTool.clicked.connect(self.outFolderToolClicked)
        # Output name
        self.outNameText = self.findChild(QLineEdit, 'outNameText')
        # Output frame count
        self.outFrameCount = self.findChild(QSpinBox, 'outFrameCount')
        # Resizing checkbox
        self.resizeCheckbox = self.findChild(QCheckBox, 'resizeCheckbox')
        # Resizing width
        self.resizeWidth = self.findChild(QSpinBox, 'resizeWidth')
        # Resizing height
        self.resizeHeight = self.findChild(QSpinBox, 'resizeHeight')
        # Go button
        self.goButton = self.findChild(QPushButton, 'goButton')
        self.goButton.clicked.connect(self.startProcessing)

        ### Show the gui ###
        self.show()
    
    def inFileToolClicked(self):
        fname = QFileDialog.getOpenFileName(self, 'Open file', '~/')
        self.inFileText.setText(fname[0])

    def outFolderToolClicked(self):
        fname = QFileDialog.getExistingDirectory(self, 'Open file', '~/')
        self.outFolderText.setText(fname)

    def startProcessing(self):
        # Get all the GUI inputs and print to terminal for debugging
        inFile = self.inFileText.text()
        outFolder = self.outFolderText.text()
        outName = self.outNameText.text()
        outFrameCount = self.outFrameCount.value()
        resize = self.resizeCheckbox.isChecked()
        resizeWidth = self.resizeWidth.value()
        resizeHeight = self.resizeHeight.value()
        print(inFile, outFolder, outName, outFrameCount, resize, resizeWidth, resizeHeight)
        # Run the vid2photogrammetry extraction function
        vid2photogrammetry.extractFrames(inFile, outFolder, outName, "png", outFrameCount)
        # If resizing enabled, run vid2photogrammetry resizing function
        if resize:
            vid2photogrammetry.resizeFrames(outFolder, resizeWidth, resizeHeight)



def main():
    app = QApplication([])
    window = Gui()
    app.exec_()



if __name__ == '__main__':
    main()