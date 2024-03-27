def simulate_update_process_custom(n, k):
    # Инициализация состояния устройств и частей обновления
    devices = [{'parts': set(), 'received_from': {}} for _ in range(n)]
    devices[0]['parts'] = set(range(1, k+1))  # Устройство 1 имеет все части

    # Функция для определения ценности устройства
    def device_value(receiver, sender):
        return devices[receiver]['received_from'].get(sender, 0)

    # Симуляция таймслотов
    timeslots = [0] * n  # Счетчик таймслотов для каждого устройства
    all_parts = set(range(1, k+1))

    while any(all_parts - d['parts'] for d in devices[1:]):
        # Определение самой редкой части для каждого устройства
        part_count = {part: sum(part in d['parts'] for d in devices) for part in all_parts}
        rarest_parts = {i: min(all_parts - d['parts'], key=lambda p: (part_count[p], p)) if all_parts - d['parts'] else None for i, d in enumerate(devices)}

        # Сбор запросов от устройств
        requests = {i: [] for i in range(n)}
        for i, part in rarest_parts.items():
            if part is not None:
                # Выбор устройства для запроса
                candidates = [j for j in range(n) if part in devices[j]['parts']]
                target = min(candidates, key=lambda j: (len(devices[j]['parts']), j))
                requests[target].append(i)

        # Обработка запросов и отправка частей
        for sender, receivers in requests.items():
            if receivers:
                # Выбор устройства для отправки на основе ценности и количества частей
                chosen_receiver = min(receivers, key=lambda r: (device_value(sender, r), len(devices[r]['parts']), r))
                part_to_send = rarest_parts[chosen_receiver]
                if part_to_send is not None:
                    devices[sender]['received_from'][chosen_receiver] = devices[sender]['received_from'].get(chosen_receiver, 0) + 1
                    devices[chosen_receiver]['parts'].add(part_to_send)
                    timeslots[chosen_receiver] += 1

        # Увеличение таймслота для устройств, которые еще не получили все части
        for i in range(1, n):
            if all_parts - devices[i]['parts']:
                timeslots[i] += 1

    return timeslots[1:]

# Пример использования функции с вводом данных пользователя
n, k = map(int, input().split())
print(*simulate_update_process_custom(n, k))

