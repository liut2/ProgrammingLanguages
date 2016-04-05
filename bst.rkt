;;; author: Duo Tao and Tao Liu

;;; (null-bst)
;;; Return an empty tree.
(define null-bst
  (lambda ()
    '()))

;;; (null-bst? bst)(car (cdr bst))
;;; Return true (#t) if bst is empty, and false (#f) otherwise.
(define null-bst?
  (lambda (bst)
    (if (equal? bst '())
         #t
         #f)))

;;; (entry bst)
;;; return the root node of bst
(define entry
  (lambda (bst)
    ;; if bst does not contain three entries, return #f
    (if (not (equal? (length bst) 3))
         #f
         (let ([left (car (cdr bst))] [right (car (cdr (cdr bst)))])
           ;; if lefttree is list and right tree is a list and node is an integer, return node
           (if (and (and (list? left) (list? right)) (integer? (car bst)))
                (car bst)
                #f)))))

;;; (left bst)
;;; return the left subtree of bst
(define left
  (lambda (bst)
    ;; if bst does not contain three entries, return #f
    (if (not (equal? (length bst) 3))
         #f
         (let ([left (car (cdr bst))] [right (car (cdr (cdr bst)))])
           ;; if lefttree is list and right tree is a list and node is an integer, return left tree
           (if (and (and (list? left) (list? right)) (integer? (car bst)))
                (car (cdr bst))
                #f)))))

;;; (right bst)
;;; return the right subtree of bst
(define right
  (lambda (bst)
    ;; if bst does not contain three entries, return #f
    (if (not (equal? (length bst) 3))
         #f
         (let ([left (car (cdr bst))] [right (car (cdr (cdr bst)))])
           ;; if lefttree is list and right tree is a list and node is an integer, return right tree
           (if (and (and (list? left) (list? right)) (integer? (car bst)))
                (car (cdr (cdr bst)))
                #f)))))

;;; (make-bst elt left right)
;;; return a tree with elt as root, left as left subtree and right as right subtree
(define make-bst
  (lambda (elt left right)
    (if (and (and (list? left) (list? right)) (integer? elt))
        (list elt left right)
        #f)))

;;; (preorder bst)
;;; return the preorder traversal of the bst
(define preorder
  (lambda (bst)
    ;; base case
    (if (equal? null bst)
               '()
               (cons (car bst) (append (preorder (car (cdr bst))) (preorder (car (cdr (cdr bst)))))))))

;;; (inorder bst)
;;; return the inorder traversal of the bst
(define inorder
  (lambda (bst)
    ;; base case
    (if (equal? null bst)
               '()
               (append (inorder (car (cdr bst))) (cons (car bst) (inorder (car (cdr (cdr bst)))))))))

;;; (postorder bst)
;;; return the postorder traversal of the bst
(define postorder
  (lambda (bst)
    ;; base case
    (if (equal? null bst)
               '()
               (append (append (postorder (car (cdr bst))) (postorder (car (cdr (cdr bst))))) (list (car bst))))))

;;; (insert v bst)
;;; insert v into bst
(define insert
  (lambda (v bst)
    ;; base case
    (if (equal? null bst)
        (list v '() '())
        (if (= (car bst) v)
            bst
            (if (< v (car bst))
                (list (car bst) (insert v (car (cdr bst))) (cdr (cdr bst))) ; insert into left subtree
                (list (car bst) (car (cdr bst)) (insert v (car (cdr (cdr bst)))))))))) ; insert into right subtree

