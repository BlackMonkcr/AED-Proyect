let CurrentCapacity = 7;
let CurrentSize = 0;
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

function findSecret() {
    const keySecret = document.getElementById('keyFindSecret').value;

    let indexP = Hash_primary(keySecret, CurrentCapacity);
    let indexS = Hash_secondary(keySecret, CurrentCapacity);

    if (document.getElementById(`ht_primary-${indexP}`).innerHTML.includes(`{ ${keySecret} :`)) {
        return true
    } else if (document.getElementById(`ht_secondary-${indexS}`).innerHTML.includes(`{ ${keySecret} :`)) {
        return true
    } else {
        return false
    }
}

function insertHelper(key, value, type) {
    if (CurrentSize >  CurrentCapacity * 2 * MAX_FILL_FACTOR) {
        rehash();
    }

    if (type === 0) {
        let index_primary = Hash_primary(key, CurrentCapacity);
        let index_secondary = Hash_secondary(key, CurrentCapacity);

        if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_primary-${index_primary}`).innerHTML === "-") {
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
        } else {
            const temp = document.getElementById(`ht_primary-${index_primary}`).innerHTML;
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
            insertHelper(temp.split(" : ")[0].split("{ ")[1], temp.split(" : ")[1].split(" }")[0], 1);
        }

        // Agrega clases y animaciones a la celda correspondiente
        const primaryCell = document.getElementById(`ht_primary-${index_primary}`);
        primaryCell.classList.add('cell');
        primaryCell.style.animation = 'highlight 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            primaryCell.classList.remove('cell');
            primaryCell.style.animation = 'none';
        }, 1000);
    } else {
        let index_primary = Hash_primary(key, CurrentCapacity);
        let index_secondary = Hash_secondary(key, CurrentCapacity);

        if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
            document.getElementById(`ht_primary-${index_primary}`).innerHTML = "{ " + key + " : " + value + " }";
            CurrentSize--;
        } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML === "-") {
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
        } else {
            const temp = document.getElementById(`ht_secondary-${index_secondary}`).innerHTML;
            document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "{ " + key + " : " + value + " }";
            insertHelper(temp.split(" : ")[0].split("{ ")[1], temp.split(" : ")[1].split(" }")[0], 0);
        }

        // Agrega clases y animaciones a la celda correspondiente
        const secondaryCell = document.getElementById(`ht_secondary-${index_secondary}`);
        secondaryCell.classList.add('cell');
        secondaryCell.style.animation = 'highlight 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            secondaryCell.classList.remove('cell');
            secondaryCell.style.animation = 'none';
        }, 1000);
    }
}

function find() {
    const key = document.getElementById('keyFind').value;

    let index_primary = Hash_primary(key, CurrentCapacity);
    let index_secondary = Hash_secondary(key, CurrentCapacity);

    if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
        // Agrega clases y animaciones a la celda correspondiente
        const primaryCell = document.getElementById(`ht_primary-${index_primary}`);
        primaryCell.classList.add('cell');
        primaryCell.style.animation = 'highlight-find 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            primaryCell.classList.remove('cell');
            primaryCell.style.animation = 'none';
            alert("Value: " + document.getElementById(`ht_primary-${index_primary}`).innerHTML.split(" : ")[1].split(" }")[0]);
        }, 2000);
    } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
        // Agrega clases y animaciones a la celda correspondiente
        const primaryCell = document.getElementById(`ht_primary-${index_primary}`);
        primaryCell.classList.add('cell');
        primaryCell.style.animation = 'highlight-find 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            primaryCell.classList.remove('cell');
            primaryCell.style.animation = 'none';
            alert("Value: " + document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.split(" : ")[1].split(" }")[0]);
        }, 2000);
    } else {
        alert("Key not found!");
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
    
    let index_primary = Hash_primary(key, CurrentCapacity);
    let index_secondary = Hash_secondary(key, CurrentCapacity);

    if (document.getElementById(`ht_primary-${index_primary}`).innerHTML.includes(`{ ${key} :`)) {
        document.getElementById(`ht_primary-${index_primary}`).innerHTML = "-";
        CurrentSize--;
        // Agrega clases y animaciones a la celda correspondiente
        const primaryCell = document.getElementById(`ht_primary-${index_primary}`);
        primaryCell.classList.add('cell');
        primaryCell.style.animation = 'highlight-remove 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            primaryCell.classList.remove('cell');
            primaryCell.style.animation = 'none';
        }, 1000);
    } else if (document.getElementById(`ht_secondary-${index_secondary}`).innerHTML.includes(`{ ${key} :`)) {
        document.getElementById(`ht_secondary-${index_secondary}`).innerHTML = "-";
        CurrentSize--;
        // Agrega clases y animaciones a la celda correspondiente
        const primaryCell = document.getElementById(`ht_primary-${index_primary}`);
        primaryCell.classList.add('cell');
        primaryCell.style.animation = 'highlight-remove 2s';

        // Elimina las clases y la animación después de la transición
        setTimeout(() => {
            primaryCell.classList.remove('cell');
            primaryCell.style.animation = 'none';
        }, 1000);
    } else {
        alert("Key not found!");
        return;
    }
    size.innerHTML = "Size: " + CurrentSize;
}

function rehash() {
    let oldCapacity = CurrentCapacity 
    CurrentCapacity *= 2;
    while (true) {
        let isPrime = true;
        for (let i = 2; i < CurrentCapacity; i++) {
            if (CurrentCapacity % i === 0) {
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
        if (document.getElementById(`ht_primary-${i}`).innerHTML !== "-") {
            elements.push(document.getElementById(`ht_primary-${i}`).innerHTML);
        } if (document.getElementById(`ht_secondary-${i}`).innerHTML !== "-") {
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