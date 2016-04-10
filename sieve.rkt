;;; author : Tao Liu. This is an individual assignment.


;;; (seq first last). This function takes two integers and returns an
;;; integer lazy list containing the sequence of values first, first+1, ... , last.
(define seq
  (lambda (first last)
    (if (> first last)
        #f
        (cons first
              (lambda () (seq (+ first 1) last))))))

;;; (inf-seq first). This function takes an integer and returns an integer lazy list
;;; containing the infinite sequence of values first,first+1, ....
(define inf-seq
  (lambda (first)
    (cons first
          (lambda () (inf-seq (+ first 1))))))

;;; (first-n lazy-list n). This function takes a lazy list and an integer and returns
;;; an ordinary Scheme list containing the first n values in the lazy-list.
(define first-n
  (lambda (lazy-list n)
    (cond ((not lazy-list) '()) ; base case 1: return '() if lazy-list is empty
          ((= n 0) '()) ; base case 2: return '() if n counts down to 0
          (else (cons (car lazy-list)
                      (first-n ((cdr lazy-list)) (- n 1)))))))

;;; (nth lazy-list n). This function takes a lazy list and an integer and
;;; returns the n-th value in the lazy-list (counting from 1).
(define nth
  (lambda (lazy-list n)
    (cond ((not lazy-list) #f) ; base case 1: return #f if lazy-list is empty
          ((= n 1) (car lazy-list)) ; base case 2: return nth when n counts down to 1
          (else (nth ((cdr lazy-list)) (- n 1))))))

;;; (filter-multiples lazy-list n). This function returns a new lazy list that has n
;;; and all integer multiples of n removed from lazy-list. 
(define filter-multiples
  (lambda (lazy-list n)
    (if (not lazy-list)
        #f ; base case: return #f if lazy-list is empty
        (let ([func (lambda () (filter-multiples ((cdr lazy-list)) n))])
          (if (not (divisible (car lazy-list) n))
              ;; including current item if it's not a multiple of n
              (cons (car lazy-list) func)
              ;; else don't include it
              (func))))))

;;; (divisible multiple n). This is a helper function trying to determine if a multiple
;;; is divisible by n.
(define divisible
  (lambda (multiple n)
    (if (integer? (/ multiple n))
        #t
        #f)))

;;; (sieve lazy-list). This function is a helper function that "sieves" the first item from the rest,
;;; returning a new lazy list.
(define sieve
  (lambda (lazy-list)
    (if (not lazy-list)
        #f
        (cons (car lazy-list)
              (lambda () (sieve (filter-multiples lazy-list (car lazy-list))))))))

;;; (primes). This function computes a lazy list containing all prime numbers,
;;; starting at 2, using the "Sieve of Eratosthenes."
(define primes
  (lambda ()
    (sieve (inf-seq 2))))
        

          
           