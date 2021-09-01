#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <QMetaType>
typedef int GroupNumber; // GroupNumber, 0 means undefined
struct Student{
    QString code{};
    QString name{};
    QString form{};
    GroupNumber groupBelongsTo{};

    Student() = default;
    Student(const QString& code, const QString& name, const QString& form):code(code), name(name), form(form){}
};

Q_DECLARE_METATYPE(Student);

#endif // STUDENT_H
