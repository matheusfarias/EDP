node_position _btree_remove_node(node_t *node, int key, int order) {
	// Para mais informações, consulte a documentação,
	// em especial o pseudo-código B-Tree-Remove-Node
	int pos;
	if (_node_find_key(node, key, &pos)) {
		// Caso a chave está foi encontrada nesse nó
		if (node->is_leaf) {
			/*
			    Caso 1: Se a chave k está em um nó x e x é uma
			    folha, remova a chave k de x
			 */

			free(node->keys[pos]);
			node->n_keys--;

			_node_deslocate_keys_up(node, node, pos, node->n_keys, 0, 1);

			return _node_position_new(node, pos);
		}
		else {
			/*
			    Caso 2: Se a chave k está em um nó x e x é um nó
			    interno.
			 */
			node_t *left = node->children[pos];
			node_t *right = node->children[pos+1];
			if (left->n_keys >= order) {
				/*
				    a) Se o nó filho y que precede k no nó x
				    tem pelo menos t chaves, encontre o
				    predecessor k’ de k na subárvore
				    enraizada em y.
				    Remova k’, e substitua k por k’ em x.
				 */
				free(node->keys[pos]);

				node_position max = _node_find_max(left);
				pair_t *p = _pair_copy(max.node->keys[max.index]);

				node->keys[pos] = p;

				_btree_remove_node(left, p->key, order);
				return _node_position_new(node, pos);
			}
			else if (right->n_keys >= order) {
				/*
				    b) Caso simétrico ao 2a. Se o nó filho y que
				    precede k no nó x tem menos que t chaves,
				    examine o nó filho z que vem depois de
				    k no nó x.
				 */

				free(node->keys[pos]);

				node_position min = _node_find_min(right);
				pair_t *p = _pair_copy(min.node->keys[min.index]);
				node->keys[pos] = p;

				_btree_remove_node(right, p->key, order);
				return _node_position_new(node, pos);
			}
			else {
				/*
				    2c) Se ambos os nós filhos y e z possuem
				    apenas t-1 chaves, concatena-se k e todo o
				    conteúdo de z com y, de maneira que x perca
				    a chave k e o ponteiro para z
				 */

				left->keys[order-1] = node->keys[pos];

				_node_deslocate_keys_up(left, right, 0, order-1, order, 0);
				_node_deslocate_children_up(left, right, 0, order, order, 0);
				left->n_keys = 2*order - 1;

				_node_delete(right);

				_node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
				_node_deslocate_children_up(node, node, pos, node->n_keys-1, 1, 2);
				node->n_keys--;

				return _btree_remove_node(left, key, order);
			}
		}
	}
	else {
		if (node->is_leaf) {
			/*
			    key não foi encontrada em um nó folha => key não
			    pertence à árvore
			 */
			return _node_position_new(NULL, -1);
		}

		/*
		        Caso 3: se a chave k não está presente em um nó interno x,
		        determine a raiz x.ci da subárvore que deve conter k.
		 */

		node_t *next = node->children[pos];

		if (next->n_keys == order-1) {
			node_t *left = next;

			node_t *right;
			if (pos == node->n_keys) {
				node_t *tmp = left;
				left = node->children[pos-1];
				right = tmp;
			}
			else {
				right = node->children[pos+1];
			}

			if (left->n_keys >= order) {
				/*
					a-left) Se x.c[i] tiver apenas t-1 chaves, mas possui o irmão
					esquerdo imediato com pelo menos t chaves, mover uma chave de x
					para x.c[i].
					Mover para x uma chave do irmão imediato esquerdo de x.c[i].
					Mover os ponteiros associados para que apontem para os filhos
					corretos.
				 */
		

				node_position max = _node_find_max(left);
				pair_t *p = _pair_copy(max.node->keys[max.index]);

				
				_btree_remove_node(left, p->key, order);

				
				_btree_insert_nonfull(right, node->keys[pos-1], order);

			
				node->keys[pos-1] = p;

				return _btree_remove_node(right, key, order);
			}
			else if (right->n_keys >= order) {
				/*
					a-right) Se x.c[i] tiver apenas t-1 chaves, mas possui o irmão
					direito imediato com pelo menos t chaves, mover uma chave de x
					para x.c[i].
					Mover para x uma chave do irmão imediato direito de x.c[i].
					Mover os ponteiros associados para que apontem para os filhos
					corretos.
				 */
			

				node_position min = _node_find_min(right);
				pair_t *p = _pair_copy(min.node->keys[min.index]);

				
				_btree_remove_node(right, p->key, order);

				
				_btree_insert_nonfull(left, node->keys[pos-1], order);

			
				node->keys[pos-1] = p;

				return _btree_remove_node(left, key, order);
			}
			else {
				/*
					b) Se x.c[i] e ambos os seus irmãos imediatos tiverem t-1
					chaves, concatenar x.c[i] com um de seus irmãos.
					Essa concatenação envolve mover uma chave de x para o novo
					nó criado com a concatenação, para que ele se torne a chave
					mediana desse novo nó.
				 */
			
				left->keys[order-1] = node->keys[pos-1];
				_node_deslocate_keys_up(node, node, pos, node->n_keys-1, 0, 1);
				_node_deslocate_children_up(node, node, pos+1, node->n_keys, 0, 1);
				node->n_keys--;

				_node_deslocate_keys_up(left, right, 0, order-1, order, 0);
				_node_deslocate_children_up(left, right, 0, right->n_keys+1, order-1, 0);
				_node_delete(right);

				left->n_keys = 2*order-1;
				return _btree_remove_node(left, key, order);
			}
		}

		return _btree_remove_node(next, key, order);
	}
}