#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stddef.h>

#define STR_LEN 64
#define DATE_LEN 20

/* Adelanto de struct para evitar líos */
typedef struct Sale Sale;

/* =======================
   Estructuras principales
   ======================= */

typedef struct {
    int id;
    char marca[STR_LEN];
    char modelo[STR_LEN];
    int anio;
    double precio;
    int kilometraje;
    int esNuevo;    /* 1 = nuevo, 0 = usado */
    int disponible; /* 1 = disponible, 0 = vendido */
} Vehicle;

typedef struct {
    Vehicle *vehiculos;
    size_t size;
    size_t capacity;

    /* Ventas en memoria */
    Sale *sales;
    size_t sales_size;
    size_t sales_capacity;
} Inventory;

typedef struct {
    char marca[STR_LEN];   /* "" indiferente */
    char modelo[STR_LEN];  /* "" indiferente */
    int minAnio;           /* 0 indiferente */
    int maxAnio;           /* 0 indiferente */
    double maxPrecio;      /* 0 indiferente */
    int maxKilometraje;    /* 0 indiferente */
    int requiereNuevo;     /* -1 indiferente, 1 nuevo, 0 usado */
} Requirement;

typedef struct {
    char nombre[STR_LEN];
    int edad;
    double presupuesto;
    char marcaPreferida[STR_LEN];   /* "" indiferente */
    char modeloPreferido[STR_LEN];  /* "" indiferente */
    int requiereNuevo;              /* -1 indiferente, 1 nuevo, 0 usado */
    int maxKilometraje;             /* 0 indiferente */
    int minAnio;                    /* 0 indiferente */
    int maxResultados;              /* 0 = todos */
} Client;

struct Sale {
    int sale_id;
    int vehicle_id;
    char buyer[STR_LEN];
    char seller[STR_LEN];
    double price;
    char date[DATE_LEN]; /* YYYY-MM-DD */
};

/* =======================
   Inicialización / memoria
   ======================= */

void initInventory(Inventory *inv);
void freeInventory(Inventory *inv);

/* =======================
   Operaciones de inventario
   ======================= */

int addVehicle(Inventory *inv, const Vehicle *v);
int removeVehicleById(Inventory *inv, int id);
Vehicle *findVehicleById(Inventory *inv, int id);
int updateVehicle(Inventory *inv, int id, const Vehicle *v);

/* =======================
   Búsquedas
   ======================= */

Vehicle *findVehiclesByRequirement(
    Inventory *inv,
    const Requirement *req,
    size_t *out_count
);

Vehicle *findVehiclesForClient(
    Inventory *inv,
    const Client *c,
    size_t *out_count
);

/* =======================
   Listado / utilidades
   ======================= */

void listVehicles(const Inventory *inv);
void printVehicle(const Vehicle *v);

/* =======================
   Ventas (solo en memoria)
   ======================= */

int registerSale(
    Inventory *inv,
    int vehicleId,
    const char *buyer,
    const char *seller,
    double price
);

void listSales(const Inventory *inv);

/* =======================
   Estado del vehículo
   ======================= */

int markSold(Inventory *inv, int id);
int markAvailable(Inventory *inv, int id);

/* =======================
   Generadores de ID
   ======================= */

int getNextId(void);
void setNextId(int start);

int getNextSaleId(void);
void setNextSaleId(int start);

#endif /* FUNCIONES_H */
