from pymodbus.client.sync import ModbusSerialClient as ModbusClient
client = ModbusClient(method='rtu', port='/dev/pts/9',baudrate=38400, timeout=1, parity='N', stopbits=1)
response = client.read_holding_registers(250, 2, unit=1)
print(response.registers)
