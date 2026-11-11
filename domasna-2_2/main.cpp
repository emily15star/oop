#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//proverka dali e prateno

struct File {
private:
    string name;
    string extension;
    uint64_t byteSize;

public:
    // Setтери и Getтери за File
    void setName(const string &n) { name = n; }
    void setExtension(const string &e) { extension = e; }
    void setByteSize(uint64_t size) { byteSize = size; }

    string getName() const { return name; }
    string getExtension() const { return extension; }
    uint64_t getByteSize() const { return byteSize; }

    string getFullFilename() {
        return name + '.' + extension;
    }
};

struct Directory; // Напред декларација

struct Directory {
private:
    string name;
    vector<File *> files;
    vector<Directory *> dirs;
    Directory *parent = nullptr;

public:
    // Setтери и Getтери за Directory
    void setName(const string &n) { name = n; }
    string getName() const { return name; }
    Directory* getParent() const { return parent; }
    void setParent(Directory *p) { parent = p; }

    const vector<File*>& getFiles() const { return files; }
    const vector<Directory*>& getDirs() const { return dirs; }

    // Прототип за големина за да може да се повикува во addFile/addDirectory доколку затреба
    uint64_t getDirectorySize() {
        uint64_t sz = 0;
        for (size_t i = 0; i < files.size(); i++) {
            sz += files[i]->getByteSize();
        }
        for (size_t i = 0; i < dirs.size(); i++) {
            sz += dirs[i]->getDirectorySize();
        }
        return sz;
    }

    // 0. Add file
    bool addFile(File &f) {
        for (size_t i = 0; i < files.size(); i++) {
            if (files[i]->getFullFilename() == f.getFullFilename()) {
                return false;
            }
        }

        for (size_t i = 0; i < dirs.size(); i++) {
            if (dirs[i]->getName() == f.getFullFilename()) {
                return false;
            }
        }

        files.push_back(&f);
        return true;
    }

    // 0. Add directory
    bool addDirectory(Directory &child) {
        for (size_t i = 0; i < dirs.size(); i++) {
            if (dirs[i]->getName() == child.name) {
                return false;
            }
        }

        for (size_t i = 0; i < files.size(); i++) {
            if (files[i]->getFullFilename() == child.name) {
                return false;
            }
        }

        child.parent = this;
        dirs.push_back(&child);
        return true;
    }

    // 1. Directory printing
    void printDir() {
        cout << "d: " << name << '\n';

        for (size_t i = 0; i < dirs.size(); i++) {
            dirs[i]->printDir();
        }

        for (size_t i = 0; i < files.size(); i++) {
            cout << " f " << files[i]->getFullFilename() << '\n';
        }

        cout << "Size: " << getDirectorySize() << " B\n";
    }

    // 2. Up function
    Directory* Up() {
        if (parent == nullptr) {
            cout << "/(root)" << endl;
            return nullptr;
        }
        return parent;
    }

    // 3. Find function
    bool Find(const string &targetName) {
        for (size_t i = 0; i < files.size(); i++) {
            if (files[i]->getFullFilename() == targetName) {
                return true;
            }
        }

        for (size_t i = 0; i < dirs.size(); i++) {
            if (dirs[i]->name == targetName) {
                return true;
            }

            if (dirs[i]->Find(targetName)) {
                return true;
            }
        }

        return false;
    }

    // Move file
    bool moveFile(const string &filename, Directory &to) {
        for (size_t i = 0; i < files.size(); i++) {
            if (filename == files[i]->getFullFilename()) {
                File *fileToMove = files[i];

                if (!to.addFile(*fileToMove)) {
                    return false;
                }

                for (size_t j = i; j < files.size() - 1; j++) {
                    files[j] = files[j + 1];
                }

                files.pop_back();
                return true;
            }
        }

        return false;
    }
};

int main() {
    Directory my;
    my.setName("documents");

    Directory child;
    child.setName("Child One");

    Directory child2;
    child2.setName("Child Two");

    File x, y, z;

    x.setName("X");
    x.setExtension("txt");
    x.setByteSize(1024);

    y.setName("Y");
    y.setExtension("jpeg");
    y.setByteSize(56281022);

    z.setName("z");
    z.setExtension("mov");
    z.setByteSize(155641022);

    my.addFile(x);
    my.addFile(y);
    my.addFile(z);

    my.addDirectory(child);
    child.addDirectory(child2);
    
    cout << "AFTER MOVE" << endl;
    child.printDir();

    my.moveFile(z.getFullFilename(), child);

    my.printDir();

    if (child.Up() != nullptr) {
        cout << "Up from child: " << child.Up()->getName() << endl;
    }

    if (my.Up() == nullptr) {
        // my е root
    }

    if (my.Find("z.mov")) {
        cout << "Found!" << endl;
    } else {
        cout << "Not found!" << endl;
    }

    cout << "Total size: " << my.getDirectorySize() << " B" << endl;

    return 0;
}