
/**
 * https://codereview.stackexchange.com/questions/165408/resource-manager-in-c-for-games
 * @param {string} S 
 * @returns 
 */
function createSingleton(S){
    const template = `
class ${S} {
    public:
        static ${S}& getInstance() {
            static ${S} instance;
            return instance;
        }

    private:
        ${S}() {}
        ${S}(${S} const&) = delete;
        void operator=(${S} const&) = delete;
};
    `;
    return template;
}

// command: node generate-singleton-template.mjs <SingletonName>
const args = process.argv.slice(2);
const S = args[0];
const template = createSingleton(S);
console.log(template);
