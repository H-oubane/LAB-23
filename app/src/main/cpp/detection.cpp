#include <jni.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <android/log.h>
#include <sys/ptrace.h>
#include <unistd.h>

#define LOG_TAG "SECURITE_NATIVE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// --------------------------------------------------
// Controle 1 : detection de supervision
// --------------------------------------------------
static bool estSupervise() {
    long resultat = ptrace(PTRACE_TRACEME, 0, 0, 0);
    if (resultat == -1) {
        LOGE("Comportement suspect : supervision detectee");
        return true;
    }
    LOGI("Aucune supervision detectee");
    return false;
}

// --------------------------------------------------
// Controle 2 : recherche de modules suspects dans la memoire
// --------------------------------------------------
static bool contientModulesSuspects() {
    FILE* fichierMaps = fopen("/proc/self/maps", "r");
    if (!fichierMaps) {
        LOGW("Impossible d'ouvrir /proc/self/maps");
        return false;
    }

    char ligne[512];

    while (fgets(ligne, sizeof(ligne), fichierMaps)) {
        if (strstr(ligne, "frida") ||
            strstr(ligne, "xposed") ||
            strstr(ligne, "libfrida") ||
            strstr(ligne, "gdbserver") ||
            strstr(ligne, "libgdb") ||
            strstr(ligne, "magisk") ||
            strstr(ligne, "substrate")) {
            LOGE("Module suspect trouve dans maps : %s", ligne);
            fclose(fichierMaps);
            return true;
        }
    }

    fclose(fichierMaps);
    LOGI("Aucun module suspect trouve");
    return false;
}

// --------------------------------------------------
// Controle global appele depuis Java
// --------------------------------------------------
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_monjnidemo_MainActivity_estEnvironnementSuspect(
        JNIEnv* env,
        jobject /* this */) {

    bool supervise = estSupervise();
    bool modulesSuspects = contientModulesSuspects();

    if (supervise || modulesSuspects) {
        LOGE("Statut securite : ENVIRONNEMENT SUSPECT");
        return JNI_TRUE;
    }

    LOGI("Statut securite : ENVIRONNEMENT SAIN");
    return JNI_FALSE;
}

// --------------------------------------------------
// Fonctions JNI du laboratoire precedent (adapteese)
// --------------------------------------------------
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_monjnidemo_MainActivity_salutDeJNI(
        JNIEnv* env,
        jobject /* this */) {
    return env->NewStringUTF("Bonjour depuis C++ via JNI !");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_monjnidemo_MainActivity_factoriel(
        JNIEnv* env,
        jobject /* this */,
        jint n) {

    if (n < 0) {
        return -1;
    }

    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }

    return static_cast<jint>(fact);
}