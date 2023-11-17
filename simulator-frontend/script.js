var CurrentCapacity = 7;
var CurrentSize = 0;
const MAX_FILL_FACTOR = 0.70;
const hashTableCuckoo = document.getElementById('HashTablesCuckoo');
const size = document.getElementById('size');
const capacity = document.getElementById('capacity');

const Hash_primary = (value, Capacity) => {
    return value % Capacity;
}

const Hash_secondary = (value, Capacity) => {
    return Math.floor(value / Capacity)%Capacity;
}

document.addEventListener('DOMContentLoaded', function() {
    size.innerHTML = "Size: " + CurrentSize;
    capacity.innerHTML = "Capacity: " + CurrentCapacity;

    for (let i = 0; i < CurrentCapacity; i++) {
        const tr = document.createElement('tr');

        tr.innerHTML = `
            <td id="${i}">${i}</td>
            <td class="ghost-1"></td>
            <td id="ht_primary-${i}">-</td>
            <td class="ghost-2"></td>
            <td id="ht_secondary-${i}">-</td>
        `;

        hashTableCuckoo.appendChild(tr);
    }
});

function insertHelper(key, value, type) {
    if (CurrentSize >  CurrentCapacity * 2 * MAX_FILL_FACTOR) {
        rehash();
    }

    if (type == 0) {
        index_primary = Hash_primary(key, CurrentCapacity);

        if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_primary-${index_primary}`).innerHTML == "-") {
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
        } else {
            const temp = document.getElementById(`ht_primary-${index_primary}`).innerHTML;
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
            insertHelper(temp.split(" : ")[0].split("{ ")[1], temp.split(" : ")[1].split(" }")[0], 1);
        }
    } else {
        index_secondary = Hash_secondary(key, CurrentCapacity);

        if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML == "-") {
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
        } else {
            const temp = document.getElementById(`ht_secondary-${index_secondary}`).innerHTML;
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
            insertHelper(temp.split(" : ")[0].split("{ ")[1], temp.split(" : ")[1].split(" }")[0], 0);
        }
    }
}

function insert() {
    CurrentSize++;
    const key = document.getElementById('keyInsert').value;
    const value = document.getElementById('valueInsert').value;

    insertHelper(key, value, 0);
    size.innerHTML = "Size: " + CurrentSize;
}

function remove() {
    const key = document.getElementById('keyRemove').value;
    
    index_primary = Hash_primary(key, CurrentCapacity);
    index_secondary = Hash_secondary(key, CurrentCapacity);

    if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
        document.getElementById(`ht_primary-${index_primary}`).innerHTML = "-";
        CurrentSize--;
    } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
        document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "-";
        CurrentSize--;
    } else {
        alert("Key not found!");
        return;
    }
    size.innerHTML = "Size: " + CurrentSize;
}

function find() {
    const key = document.getElementById('keyFind').value;

    index_primary = Hash_primary(key, CurrentCapacity);
    index_secondary = Hash_secondary(key, CurrentCapacity);

    if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
        alert("Value: " + document.getElementById(`ht_primary-${index_primary}`).innerHTML.split(" : ")[1].split(" }")[0]);
        return;
    } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
        alert("Value: " + document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.split(" : ")[1].split(" }")[0]);
        return;
    } else {
        alert("Key not found!");
        return;
    }
}

function rehash() {
    let oldCapacity = CurrentCapacity 
    CurrentCapacity *= 2;
    while (true) {
        let isPrime = true;
        for (let i = 2; i < CurrentCapacity; i++) {
            if (CurrentCapacity % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            break;
        }
        CurrentCapacity++;
    }
    
    capacity.innerHTML = "Capacity: " + CurrentCapacity;

    // Recolecta todos los elementos de las tablas hash en un array
    const elements = [];

    for (let i = 0; i < oldCapacity; i++) {
        if (document.getElementById(`ht_primary-${i}`).innerHTML != "-") {
            elements.push(document.getElementById(`ht_primary-${i}`).innerHTML);
        } if (document.getElementById(`ht_secondary-${i}`).innerHTML != "-") {
            elements.push(document.getElementById(`ht_secondary-${i}`).innerHTML);
        }
    }

    hashTableCuckoo.innerHTML = "";

    hashTableCuckoo.innerHTML = `
        <tr>
            <th>Index</th>
            <th class="ghost-1"></th>
            <th>HashTable 1</th>
            <th class="ghost-2"></th>
            <th>HashTable 2</th>
        </tr>
    `;

    for (let i = 0; i < CurrentCapacity; i++) {
        const tr = document.createElement('tr');

        tr.innerHTML = `
            <td id="${i}">${i}</td>
            <td class="ghost-1"></td>
            <td id="ht_primary-${i}">-</td>
            <td class="ghost-2"></td>
            <td id="ht_secondary-${i}">-</td>
        `;

        hashTableCuckoo.appendChild(tr);
    }

    // Inserta los elementos en la nueva tabla hash
    for (let i = 0; i < elements.length; i++) {
        insertHelper(elements[i].split(" : ")[0].split("{ ")[1], elements[i].split(" : ")[1].split(" }")[0], 0);
    }
}