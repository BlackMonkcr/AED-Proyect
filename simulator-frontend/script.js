var CurrentCapacity = 5;

const Hash_primary = (value, Capacity) => {
    return value % Capacity;
}

const Hash_secondary = (value, Capacity) => {
    return Math.floor(value / Capacity)%Capacity;
}

document.addEventListener('DOMContentLoaded', function() {
    const hashTableCuckoo = document.getElementById('HashTablesCuckoo');

    for (let i = 0; i < CurrentCapacity; i++) {
        const tr = document.createElement('tr');

        tr.innerHTML = `
            <td id="${i}">${i}</td>
            <td class="ghost-1"></td>
            <td id="ht_primary-${i}"></td>
            <td class="ghost-2"></td>
            <td id="ht_secondary-${i}"></td>
        `;

        hashTableCuckoo.appendChild(tr);
    }
});

function insert() {
    const key = document.getElementById('keyInsert').value;
    const value = document.getElementById('valueInsert').value;

    const ht_primary = document.getElementById(`ht_primary-${Hash_primary(key, CurrentCapacity)}`);
    const ht_secondary = document.getElementById(`ht_secondary-${Hash_secondary(key, CurrentCapacity)}`);

    if (ht_primary.innerHTML == "") {
        ht_primary.innerHTML = value;
    } else if (ht_secondary.innerHTML == "") {
        ht_secondary.innerHTML = value;
    }
}