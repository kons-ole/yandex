def simulate_update_process_detailed(n, k):
    # Инициализация состояния устройств и частей обновления
    devices = [{'parts': set(), 'received_from': {}, 'value_to_others': {}} for _ in range(n)]
    devices[0]['parts'] = set(range(1, k+1))  # Устройство 1 имеет все части

    # Функция для определения ценности устройства
    def device_value(receiver, sender):
        # print(devices[receiver]['received_from'].get(sender, 0))
        return devices[receiver]['received_from'].get(sender, 0)

    # Симуляция таймслотов
    timeslots = [0] * n  # Счетчик таймслотов для каждого устройства
    all_parts = set(range(1, k+1))

    while any(all_parts - d['parts'] for d in devices[1:]):
        prev_states = [d['parts'].copy() for d in devices]
        # Определение самой редкой части для каждого устройства
        part_count = {part: sum(part in d['parts'] for d in devices) for part in all_parts}
        # print(part_count)
        rarest_parts = {i: min(all_parts - d['parts'], key=lambda p: (part_count[p], p)) if all_parts - d['parts'] else None for i, d in enumerate(devices)}
        # print(rarest_parts)
        # Сбор запросов от устройств
        requests = {i: [] for i in range(n)}
        for i, part in rarest_parts.items():
            if part is not None:
                # Выбор устройства для запроса
                candidates = [j for j in range(n) if part in devices[j]['parts']]
                target = min(candidates, key=lambda j: (len(devices[j]['parts']), j))
                requests[target].append(i)
        # print(requests)
        # Обработка запросов и отправка частей
                # print('meow')
        for sender, receivers in requests.items():
            if receivers:
                # print(receivers)
                # Выбор устройства для отправки на основе ценности и количества частей
                chosen_receiver = min(receivers, key=lambda r: (-device_value(sender, r), len(devices[r]['parts']), r))
                part_to_send = rarest_parts[chosen_receiver]
                # print(chosen_receiver)
                if part_to_send is not None:
                    devices[sender]['value_to_others'][chosen_receiver] = devices[sender]['value_to_others'].get(chosen_receiver, 0) + 1
                    devices[chosen_receiver]['parts'].add(part_to_send)
                    devices[chosen_receiver]['received_from'][sender] = devices[chosen_receiver]['received_from'].get(sender, 0) + 1
                    timeslots[chosen_receiver] += 1
        for i, (prev_state, device) in enumerate(zip(prev_states, devices)):
            if i != 0:
                # Проверяем, получило ли устройство новую часть и имеет ли оно уже все части
                if prev_state == device['parts'] and all_parts - device['parts']:
                    # Устройство i не получило передачу в этом таймслоте и еще не имеет всех частей
                    timeslots[i] += 1

    return timeslots[1:]


n, k = map(int, input().split())

# Тестирование функции с примером из задания
print(*simulate_update_process_detailed(n, k))