import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QAction, QPushButton, QLabel, QVBoxLayout
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import pyqtSlot


# class App(QMainWindow):
#     def __init__(self):
#         super().__init__()
#         self.title = 'Settings'
#         self.left = 10
#         self.top = 10
#         self.width = 640
#         self.height = 480
#         self.window()
#         self.menu()

#     def window(self):
#         self.setWindowTitle(self.title)
#         self.setGeometry(self.left, self.top, self.width, self.height)
#         self.show()

#     def menu(self):
#         self.setWindowTitle(self.title)
#         self.setGeometry(self.left, self.top, self.width, self.height)

#         mainMenu = self.menuBar()
#         fileMenu = mainMenu.addMenu('File')
#         editMenu = mainMenu.addMenu('Edit')
#         viewMenu = mainMenu.addMenu('View')
#         searchMenu = mainMenu.addMenu('Search')
#         toolsMenu = mainMenu.addMenu('Tools')
#         helpMenu = mainMenu.addMenu('Help')

#         exitButton = QAction(QIcon('exit24.png'), 'Exit', self)
#         exitButton.setShortcut('Ctrl+Q')
#         exitButton.setStatusTip('Exit application')
#         exitButton.triggered.connect(self.close)
#         fileMenu.addAction(exitButton)

#         self.show()

#         self.central_widget = QWidget()
#         self.setCentralWidget(self.central_widget)
#         lay = QVBoxLayout(self.central_widget)
#         label = QLabel(self)
#         pixmap = QPixmap('image.jpeg')
#         label.setPixmap(pixmap)

#         lay.addWidget(label)
#         self.show()

class App(QMainWindow):

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Settings")

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        lay = QVBoxLayout(self.central_widget)

        label = QLabel(self)
        pixmap = QPixmap('image.jpeg')
        label.setPixmap(pixmap)
        self.resize(pixmap.width(), pixmap.height())

        lay.addWidget(label)
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
