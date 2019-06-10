#ifndef UTILS_H
#define UTILS_H

/*!
 * \file utils.h
 * \brief Fonctions réutilisables
 *
 * Fourni des fonctions réutilisables entre plusieurs programme, framework Qt nécessaire pour les objets QMap et QString
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QMap>
#include <QString>

/**
 * \fn QMap<QString, QString>* readArguments(int argc, char** argv, QMap<QString, QString> defaultValues = QMap<QString, QString>())
 * \brief Fonction renvoyant une QMap remplis avec les paramètres argc et argv
 *
 * Lis les arguments argv passés en paramètres et renvoie une QMap
 * Chaque argument commençant par un tiret est associé à l'argument suivant
 * Des valeurs par défauts peuvent être passées en paramètres, si un argument correspond dans la liste, la valeur par défaut est remplacée
 *
 * \param argc Le nombre d'argument dans le tableau argv**
 * \param argv Le tableau de chaines de caractères contenant les paramètres
 * \param defaultValue Les arguments à associer par défaut
 *
 * \return Une QMap associant les arguments commençant par un tiret avec l'argument suivant.
 */
QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> defaultValues = QMap<QString, QString>());

#endif // UTILS_H
