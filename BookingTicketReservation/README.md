# Reserva de boletos de cine . 

Se debe de implementar un sistema de reserva de boletos para una sala de cine. Un proceso será el encargado de administrar los lugares disponibles de la sala, 
mientras que cada comprador será un proceso diferente. 

Requerimientos:

(a) Los compradores podrán reservar n boletos en asientos no necesariamente
contiguos.

(b) Los compradores pueden regresar a cancelar la reservación de asientos 
(no es necesario verificar que sean los clientes que hayan hecho previamente la reservación).

(c) El administrador en realidad no recibe peticiones como en paso de
mensajes. Sin embargo, debe garantizar la exclusión mutua usando
variables de sincronización donde sea necesario.

(d) Al inicio de cada compra o cancelación se debe mostrar el estado de
los asientos de la sala. Es suficiente que los asientos ocupados y libres
se muestren en modo texto.
