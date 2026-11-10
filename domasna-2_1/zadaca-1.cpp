
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct File {
    string name;
    string extension;
    uint64_t byteSize;
};

string getFullFilename(File &f) {
    return f.name + '.' + f.extension;
}

struct Directory {
    string name;
    vector<File *> files;
    vector<Directory *> dirs;
    Directory *parent = nullptr;
};

// 0. Proverka dali postoi isto ime vo direktoriumot

bool canAddFile(Directory &d, File &f) {
    string filename = getFullFilename(f);

    for (File *file : d.files) {
        if (getFullFilename(*file) == filename) {
            return false;
        }
    }

    for (Directory *dir : d.dirs) {
        if (dir->name == filename) {
            return false;
        }
    }

    return true;
}

bool addFile(Directory &d, File &f) {
    if (!canAddFile(d, f)) {
        cout << "File already exists!\n";
        return false;
    }

    d.files.push_back(&f);
    return true;
}

bool addDirectory(Directory &parent, Directory &child) {
    for (Directory *dir : parent.dirs) {
        if (dir->name == child.name) {
            cout << "Directory already exists!\n";
            return false;
        }
    }

    for (File *file : parent.files) {
        if (getFullFilename(*file) == child.name) {
            cout << "File with that name already exists!\n";
            return false;
        }
    }

    child.parent = &parent;
    parent.dirs.push_back(&child);
    return true;
}

// 4. Golemina na direktoriumot, vklucuvajki gi poddirektoriumite

uint64_t getDirectorySize(Directory &d) {
    uint64_t sz = 0;

    for (File *file : d.files) {
        sz += file->byteSize;
    }

    for (Directory *dir : d.dirs) {
        sz += getDirectorySize(*dir);
    }

    return sz;
}

// Premestuvanje fajl

bool moveFile(const string &filename, Directory &from,
              Directory &to) {
    for (size_t i = 0; i < from.files.size(); i++) {
        File *file = from.files[i];

        if (filename == getFullFilename(*file)) {
            if (!canAddFile(to, *file)) {
                cout << "File already exists in destination!\n";
                return false;
            }

            from.files.erase(from.files.begin() + i);
            to.files.push_back(file);
            return true;
        }
    }

    return false;
}

// 1. Pecatenje na direktoriumot i site negovi poddirektoriumi

void printDir(Directory &d, int level = 0) {
    string indent(level * 2, ' ');

    cout << indent << "d: " << d.name << '\n';

    for (File *file : d.files) {
        cout << indent << " f: "
             << getFullFilename(*file) << '\n';
    }

    cout << indent << "Size: "
         << getDirectorySize(d) << " B\n";

    for (Directory *dir : d.dirs) {
        printDir(*dir, level + 1);
    }
}

// 2. Vrakanje na roditelskiot direktorium

Directory *Up(Directory &d) {
    if (d.parent == nullptr) {
        cout << "/(root)\n";
        return nullptr;
    }

    return d.parent;
}

// 3. Prebaruvanje fajl ili direktorium, i vo poddirektoriumi

bool Find(Directory &d, const string &target,
          const string &path = "") {
    string currentPath;

    if (path.empty()) {
        currentPath = "/" + d.name;
    } else {
        currentPath = path;
    }

    for (File *file : d.files) {
        if (getFullFilename(*file) == target) {
            cout << "Found file: " << currentPath
                 << "/" << target << '\n';
            return true;
        }
    }

    for (Directory *dir : d.dirs) {
        if (dir->name == target) {
            cout << "Found directory: " << currentPath
                 << "/" << target << '\n';
            return true;
        }
    }

    for (Directory *dir : d.dirs) {
        if (Find(*dir, target,
                 currentPath + "/" + dir->name)) {
            return true;
        }
    }

    return false;
}

int main() {
    Directory my;
    my.name = "documents";

    File x, y, z;

    x.name = "X";
    x.extension = "txt";
    x.byteSize = 1024;

    y.name = "Y";
    y.extension = "jpeg";
    y.byteSize = 56281022;

    z.name = "z";
    z.extension = "mov";
    z.byteSize = 1556281022;

    addFile(my, x);
    addFile(my, y);
    addFile(my, z);

    y.name = "YYY";

    Directory child;
    child.name = "Child One";

    addDirectory(my, child);

    printDir(my);

    moveFile(getFullFilename(z), my, child);

    cout << "\nAFTER MOVE\n";
    printDir(my);

    cout << "\nUP:\n";
    Directory *p = Up(child);
    if (p != nullptr) {
        cout << p->name << '\n';
    }

    cout << "\nFIND:\n";
    if (!Find(my, "z.mov")) {
        cout << "Not found!\n";
    }

    return 0;
}
